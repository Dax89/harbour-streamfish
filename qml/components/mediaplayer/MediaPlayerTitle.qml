import QtQuick 2.1
import Sailfish.Silica 1.0
import "../../js/TagParser.js" as TagParser

MediaPlayerItem
{
    property string title

    id: mediaplayertitle
    height: Theme.itemSizeSmall

    Label
    {
        id: lbltitle
        anchors.fill: parent
        text: TagParser.parse(title)
        elide: Text.ElideRight
        verticalAlignment: Text.AlignHCenter
        horizontalAlignment: Text.AlignRight
    }
}

