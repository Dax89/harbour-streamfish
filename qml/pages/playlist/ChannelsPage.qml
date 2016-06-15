import QtQuick 2.1
import Sailfish.Silica 1.0
import harbour.streamfish.Model 1.0
import "../../items/playlist"

Page
{
    property var playList

    id: channelspage

    SilicaFlickable
    {
        anchors.fill: parent

        PageHeader
        {
            id: pageheader
            title: qsTr("Channels")
            anchors { left: parent.left; top: parent.top; right: parent.right }
        }

        SearchField
        {
            id: searchfield
            anchors { left: parent.left; top: pageheader.bottom; right: parent.right }
            placeholderText: qsTr("Filter")
            inputMethodHints: Qt.ImhNoAutoUppercase | Qt.ImhNoPredictiveText
            labelVisible: false
            width: parent.width
        }

        SilicaListView
        {
            id: lvchannels
            anchors { left: parent.left; top: searchfield.bottom; right: parent.right; bottom: parent.bottom }
            clip: true

            model: M3UFilteredChannelsModel {
                id: channelsmodel
                playList: channelspage.playList
                filter: searchfield.text
            }

            delegate: ChannelItem {
                width: parent.width
                contentHeight: Theme.itemSizeSmall
                title: channel.name
                logo: channel.logo
                onClicked: pageStack.replace("../mediaplayer/MediaPlayerPage.qml", { "channel": channel })
            }
        }
    }
}

