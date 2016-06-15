#ifndef M3UFILTEREDCHANNELSMODEL_H
#define M3UFILTEREDCHANNELSMODEL_H

#include <QSortFilterProxyModel>
#include "m3uchannelsmodel.h"

class M3UFilteredChannelsModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(M3UPlayList* playList READ playList WRITE setPlayList NOTIFY playListChanged)
    Q_PROPERTY(QString filter READ filter WRITE setFilter NOTIFY filterChanged)

    public:
        explicit M3UFilteredChannelsModel(QObject *parent = 0);
        M3UPlayList* playList() const;
        void setPlayList(M3UPlayList* playlist);
        const QString& filter() const;
        void setFilter(const QString& filter);

    protected:
        virtual bool filterAcceptsRow(int source_row, const QModelIndex &) const;

    signals:
        void playListChanged();
        void filterChanged();

    private:
        M3UChannelsModel* _channelsmodel;
        QString _filter;
};

#endif // M3UFILTEREDCHANNELSMODEL_H
