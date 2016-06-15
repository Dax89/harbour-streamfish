import QtQuick 2.1
import Sailfish.Silica 1.0
import "../../js/TagParser.js" as TagParser

ListItem
{
    property string title
    property alias logo: imgchannel.logoUrl

    id: channelitem

    Row
    {
        anchors { fill: parent; leftMargin: Theme.paddingSmall; rightMargin: Theme.paddingSmall }
        spacing: Theme.paddingMedium

        ChannelLogo
        {
            id: imgchannel
            anchors.verticalCenter: parent.verticalCenter
            height: Theme.iconSizeSmall
            contentWidth: Theme.iconSizeSmall
        }

        Label
        {
            id: lbltitle
            text: TagParser.parse(title)
            height: parent.height
            width: parent.width - imgchannel.width
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight
        }
    }
}
