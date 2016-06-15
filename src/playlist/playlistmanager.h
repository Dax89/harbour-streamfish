#ifndef PLAYLISTMANAGER_H
#define PLAYLISTMANAGER_H

#include <QObject>
#include "playliststorage.h"

class PlayListManager : public QObject
{
    Q_OBJECT

    public:
        explicit PlayListManager(QObject *parent = 0);
        PlayListStorage* storage() const;

    public slots:
        void add(const QString &name, const QString& url);
        void load();

    private:
        PlayListStorage* _storage;
        QString _configpath;
};

#endif // PLAYLISTMANAGER_H
