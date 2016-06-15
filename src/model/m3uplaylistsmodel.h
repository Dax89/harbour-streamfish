#ifndef M3UPLAYLISTSMODEL_H
#define M3UPLAYLISTSMODEL_H

#include <QAbstractListModel>
#include "../playlist/playlistmanager.h"

class M3UPlayListsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(PlayListManager* manager READ manager WRITE setManager NOTIFY managerChanged)

    public:
         enum { PlayListRole = Qt::UserRole };

    public:
        explicit M3UPlayListsModel(QObject *parent = 0);
        PlayListManager* manager() const;
        void setManager(PlayListManager* manager);

    public:
        virtual QVariant data(const QModelIndex &index, int role) const;
        virtual int rowCount(const QModelIndex &) const;
        virtual QHash<int, QByteArray> roleNames() const;

    private slots:
        void resetModel();

    signals:
        void managerChanged();

    private:
        PlayListManager* _manager;
};

#endif // M3UPLAYLISTSMODEL_H
