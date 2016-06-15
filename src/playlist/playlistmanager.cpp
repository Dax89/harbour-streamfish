#include "playlistmanager.h"
#include <QGuiApplication>
#include <QStandardPaths>
#include <QRegularExpression>
#include <QDir>

PlayListManager::PlayListManager(QObject *parent) : QObject(parent)
{
    QString endpath = qApp->applicationName() + QDir::separator() + qApp->applicationName();
    QDir cfgdir(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation));
    cfgdir.mkpath(endpath);

    this->_configpath = cfgdir.absoluteFilePath(endpath);
    this->_storage = new PlayListStorage(this->_configpath, this);
}

PlayListStorage *PlayListManager::storage() const
{
    return this->_storage;
}

void PlayListManager::add(const QString& name, const QString &url)
{
    QString adjurl = url;

    if(url.indexOf(QRegularExpression ("^([^:]+)://")) == -1) // Fallback to HTTP
        adjurl.prepend("http://");

    M3UPlayList* playlist = new M3UPlayList(name, QUrl(adjurl), this->_storage);
    this->_storage->download(playlist);
}

void PlayListManager::load()
{
    this->_storage->load();
}
