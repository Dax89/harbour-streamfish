#include "playliststorage.h"
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QUrl>
#include <QDir>

const QString PlayListStorage::PLAYLISTS_PATH = "playlists";
const QString PlayListStorage::VERSION = "1.0";

PlayListStorage::PlayListStorage(const QString &configpath, QObject *parent) : QObject(parent)
{
    this->initFolder(configpath, PlayListStorage::PLAYLISTS_PATH, this->_plpath);
}

int PlayListStorage::playListCount() const
{
    return this->_playlists.count();
}

M3UPlayList *PlayListStorage::playListAt(int idx) const
{
    return this->_playlists.at(idx);
}

void PlayListStorage::download(M3UPlayList *playlist)
{
    connect(playlist, &M3UPlayList::loaded, this, &PlayListStorage::onPlayListLoaded);
    connect(playlist, &M3UPlayList::error, this, &PlayListStorage::onPlayListError);

    playlist->download();
}

void PlayListStorage::load()
{
    QByteArray pldata;
    this->readFile(this->playlistFile(), pldata);

    QJsonDocument jsdoc = QJsonDocument::fromJson(pldata);
    QJsonObject obj = jsdoc.object();
    QJsonArray playlists = obj["playlists"].toArray();

    foreach(QJsonValue plitem, playlists)
    {
        QJsonObject plobj = plitem.toObject();
        M3UPlayList* playlist = new M3UPlayList(plobj["name"].toString(), QUrl(plobj["url"].toString()), plobj["file"].toString(), plobj["count"].toInt(), this);
        this->_playlists.append(playlist);
    }
}

void PlayListStorage::initFolder(const QString &configpath, const QString &pathname, QString &destpath)
{
    destpath = configpath + QDir::separator() + pathname;

    QDir dir;
    dir.mkpath(destpath);
}

void PlayListStorage::readFile(const QString &infile, QByteArray &data)
{
    QFile f(infile);
    f.open(QFile::ReadOnly);
    data = f.readAll();
    f.close();
}

QString PlayListStorage::playlistPath() const
{
    return this->_plpath + QDir::separator();
}

QString PlayListStorage::playlistFile() const
{
    return this->_plpath + QDir::separator() + PlayListStorage::PLAYLISTS_PATH + ".json";
}

void PlayListStorage::updateToFile() const
{
    QJsonObject jsobj;
    QJsonArray jspl;

    foreach(const M3UPlayList* playlist, this->_playlists)
    {
        QJsonObject jsitem;
        jsitem["name"] = playlist->name();
        jsitem["count"] = playlist->channelsCount();
        jsitem["file"] = this->playlistPath() + QDir::separator() + playlist->file();
        jsitem["url"] = playlist->url().toString();

        jspl.append(jsitem);
    }

    jsobj["version"] = PlayListStorage::VERSION;
    jsobj["playlists"] = jspl;

    QJsonDocument jsdoc;
    jsdoc.setObject(jsobj);

    QFile f(this->playlistFile());
    f.open(QFile::WriteOnly);
    f.write(jsdoc.toJson());
    f.close();
}

void PlayListStorage::onPlayListError(const QString &errmsg)
{
    qWarning() << "ERROR:" << errmsg;
}

void PlayListStorage::onPlayListLoaded()
{
    M3UPlayList* playlist = qobject_cast<M3UPlayList*>(this->sender());

    this->_playlists.append(playlist);
    playlist->save(this->playlistPath());
    this->updateToFile();

    emit playListAdded();
}
