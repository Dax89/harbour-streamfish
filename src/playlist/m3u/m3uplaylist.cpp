#include "m3uplaylist.h"
#include <QCryptographicHash>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QFile>
#include <QDir>

QNetworkAccessManager* M3UPlayList::_netmgr = NULL;
const QString M3UPlayList::VERSION = "1.0";

M3UPlayList::M3UPlayList(const QString &name, const QUrl &url, QObject *parent): QObject(parent), _loaded(false), _count(0), _name(name), _url(url)
{
    this->_file = QCryptographicHash::hash(name.toUtf8(), QCryptographicHash::Md5).toHex() + ".playlist";
}

M3UPlayList::M3UPlayList(const QString &name, const QUrl &url, const QString &file, int count, QObject *parent): QObject(parent), _loaded(false), _count(count), _name(name), _file(file), _url(url)
{

}

const QString& M3UPlayList::name() const
{
    return this->_name;
}

const QString &M3UPlayList::file() const
{
    return this->_file;
}

const QUrl &M3UPlayList::url() const
{
    return this->_url;
}

int M3UPlayList::channelsCount() const
{
    if(!this->_loaded)
        return this->_count;

    return this->_channels.count();
}

M3UChannel *M3UPlayList::channelAt(int i) const
{
    return this->_channels.at(i);
}

QNetworkAccessManager *M3UPlayList::networkManager()
{
    if(!M3UPlayList::_netmgr)
        M3UPlayList::_netmgr = new QNetworkAccessManager(this->parent());

    return M3UPlayList::_netmgr;
}

void M3UPlayList::download()
{
    QNetworkReply* reply = this->networkManager()->get(QNetworkRequest(this->_url));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onDownloadError(QNetworkReply::NetworkError))); // NOTE: Overload madness
    connect(reply, &QNetworkReply::finished, this, &M3UPlayList::onDownloadFinished);
}

void M3UPlayList::save(const QString &dest)
{
    QJsonObject jsobj;
    QJsonArray jsdata;

    for(int i = 0; i < this->_channels.length(); i++)
    {
        const M3UChannel* channel = this->_channels.at(i);

        QJsonObject jspl;
        jspl["name"] = channel->name();
        jspl["url"] = channel->url().toString();
        jspl["logo"] = channel->logo();

        jsdata.append(jspl);
    }

    jsobj["version"] = M3UPlayList::VERSION;
    jsobj["channels"] = jsdata;

    QJsonDocument jsdoc;
    jsdoc.setObject(jsobj);

    QFile f(dest + QDir::separator() + this->_file);
    f.open(QFile::WriteOnly);
    f.write(jsdoc.toJson());
    f.close();
}

void M3UPlayList::load(bool force)
{
    if(!force && this->_loaded)
        return;

    QFile f(this->_file);
    f.open(QFile::ReadOnly);
    QByteArray pljsondata = f.readAll();
    f.close();

    QJsonDocument jsdoc = QJsonDocument::fromJson(pljsondata);
    QJsonArray items = jsdoc.object()["channels"].toArray();

    foreach(QJsonValue jsvalue, items)
    {
        QJsonObject jsobj = jsvalue.toObject();
        this->_channels.append(new M3UChannel(jsobj["name"].toString(), jsobj["url"].toString(), jsobj["logo"].toString(), this));
    }

    this->_loaded = true;
}

void M3UPlayList::onDownloadFinished()
{
    M3UParser m3uparser;
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender());
    QString m3udata = QString::fromUtf8(reply->readAll());

    if(!m3uparser.parse(m3udata, this->_channels, this))
    {
        this->_channels.clear(); // Invalid playlist, delete all items
        emit error(m3uparser.lastError());
    }
    else
    {
        this->_loaded = true;
        emit loaded();
    }

    reply->deleteLater();
}

void M3UPlayList::onDownloadError(QNetworkReply::NetworkError)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(this->sender());

    emit error(reply->errorString());
    reply->deleteLater();
}
