#ifndef M3UCHANNELSMODEL_H
#define M3UCHANNELSMODEL_H

#include <QAbstractListModel>
#include "../playlist/m3u/m3uplaylist.h"

class M3UChannelsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(M3UPlayList* playList READ playList WRITE setPlayList NOTIFY playListChanged)

    public:
         enum { ChannelRole = Qt::UserRole };

    public:
        explicit M3UChannelsModel(QObject *parent = 0);
        M3UPlayList* playList() const;
        void setPlayList(M3UPlayList* playlist);

    public:
        virtual QVariant data(const QModelIndex &index, int role) const;
        virtual int rowCount(const QModelIndex &) const;
        virtual QHash<int, QByteArray> roleNames() const;

    signals:
        void playListChanged();

    private:
        M3UPlayList* _playlist;
};

#endif // M3UCHANNELSMODEL_H
