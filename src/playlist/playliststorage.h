#ifndef PLAYLISTSTORAGE_H
#define PLAYLISTSTORAGE_H

#include <QObject>
#include "m3u/m3uplaylist.h"

class PlayListStorage : public QObject
{
    Q_OBJECT

    public:
        explicit PlayListStorage(const QString& configpath, QObject *parent = 0);
        int playListCount() const;
        M3UPlayList* playListAt(int idx) const;
        void download(M3UPlayList* playlist);
        void load();

    private:
        void initFolder(const QString& configpath, const QString& pathname, QString& destpath);
        void readFile(const QString& infile, QByteArray& data);
        QString playlistPath() const;
        QString playlistFile() const;
        void updateToFile() const;

    private slots:
        void onPlayListError(const QString &errmsg);
        void onPlayListLoaded();

    private:
        QList<M3UPlayList*> _playlists;
        QString _plpath;

    signals:
        void playListAdded();
        void playListRemoved();

    private:
        static const QString PLAYLISTS_PATH;
        static const QString VERSION;
};

#endif // PLAYLISTSTORAGE_H
