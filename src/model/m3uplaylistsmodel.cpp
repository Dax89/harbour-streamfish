#include "m3uplaylistsmodel.h"

M3UPlayListsModel::M3UPlayListsModel(QObject *parent) : QAbstractListModel(parent), _manager(NULL)
{

}

PlayListManager *M3UPlayListsModel::manager() const
{
    return this->_manager;
}

void M3UPlayListsModel::setManager(PlayListManager *manager)
{
    if(this->_manager == manager)
        return;

    if(this->_manager)
    {
        disconnect(this->_manager->storage(), &PlayListStorage::playListAdded, this, 0);
        disconnect(this->_manager->storage(), &PlayListStorage::playListRemoved, this, 0);
    }

    this->_manager = manager;

    connect(this->_manager->storage(), &PlayListStorage::playListAdded, this, &M3UPlayListsModel::resetModel);
    connect(this->_manager->storage(), &PlayListStorage::playListRemoved, this, &M3UPlayListsModel::resetModel);
    emit managerChanged();
}

QVariant M3UPlayListsModel::data(const QModelIndex &index, int role) const
{
    if(!this->_manager || (role != M3UPlayListsModel::PlayListRole))
        return QVariant();

    return QVariant::fromValue(this->_manager->storage()->playListAt(index.row()));
}

int M3UPlayListsModel::rowCount(const QModelIndex &) const
{
    if(!this->_manager)
        return 0;

    return this->_manager->storage()->playListCount();
}

QHash<int, QByteArray> M3UPlayListsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[M3UPlayListsModel::PlayListRole] = "playList";

    return roles;
}

void M3UPlayListsModel::resetModel()
{
    this->beginResetModel();
    this->endResetModel();
}
