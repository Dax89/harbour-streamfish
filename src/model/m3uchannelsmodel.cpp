#include "m3uchannelsmodel.h"

M3UChannelsModel::M3UChannelsModel(QObject *parent) : QAbstractListModel(parent), _playlist(NULL)
{

}

M3UPlayList *M3UChannelsModel::playList() const
{
    return this->_playlist;
}

void M3UChannelsModel::setPlayList(M3UPlayList *playlist)
{
    if(this->_playlist == playlist)
        return;

    this->_playlist = playlist;

    if(this->_playlist)
        this->_playlist->load();

    emit playListChanged();
}

QVariant M3UChannelsModel::data(const QModelIndex &index, int role) const
{
    if(!this->_playlist || (role != M3UChannelsModel::ChannelRole))
        return QVariant();

    return QVariant::fromValue(this->_playlist->channelAt(index.row()));
}

int M3UChannelsModel::rowCount(const QModelIndex &) const
{
    if(!this->_playlist)
        return 0;

    return this->_playlist->channelsCount();
}

QHash<int, QByteArray> M3UChannelsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[M3UChannelsModel::ChannelRole] = "channel";

    return roles;
}

