#include "m3ufilteredchannelsmodel.h"

M3UFilteredChannelsModel::M3UFilteredChannelsModel(QObject *parent) : QSortFilterProxyModel(parent)
{
    this->_channelsmodel = new M3UChannelsModel(this);
    connect(this->_channelsmodel, &M3UChannelsModel::playListChanged, this, &M3UFilteredChannelsModel::playListChanged);

    this->setSourceModel(this->_channelsmodel);
}

M3UPlayList *M3UFilteredChannelsModel::playList() const
{
    return this->_channelsmodel->playList();
}

void M3UFilteredChannelsModel::setPlayList(M3UPlayList *playlist)
{
    this->_channelsmodel->setPlayList(playlist);
}

const QString &M3UFilteredChannelsModel::filter() const
{
    return this->_filter;
}

void M3UFilteredChannelsModel::setFilter(const QString &filter)
{
    if(this->_filter == filter)
        return;

    this->_filter = filter;
    this->invalidate();
    emit filterChanged();
}

bool M3UFilteredChannelsModel::filterAcceptsRow(int source_row, const QModelIndex &) const
{
    M3UChannel* channel = this->_channelsmodel->data(this->_channelsmodel->index(source_row, 0), M3UChannelsModel::ChannelRole).value<M3UChannel*>();
    return this->_filter.isEmpty() || (channel->name().indexOf(this->_filter, 0, Qt::CaseInsensitive) != -1);
}

