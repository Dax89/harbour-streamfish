import QtQuick 2.1
import Sailfish.Silica 1.0

BackgroundItem
{
    property alias title: lbltitle.text
    property int channelsCount

    id: playlistitem

    function tagSurround(s, tag, attributes) {
        return "<" + tag + " " + (attributes || "") + ">" + s + "</" + tag + ">";
    }

    PanelBackground
    {
        anchors.fill: parent
        color: "transparent"
        border { color: Theme.secondaryHighlightColor; width: 1 }
    }

    Column
    {
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter

        Label
        {
            id: lbltitle
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            font { pixelSize: Theme.fontSizeExtraSmall; bold: true }
            elide: Text.ElideRight
        }

        Label
        {
            id: lblchannelscount
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignTop
            font.pixelSize: Theme.fontSizeTiny
            elide: Text.ElideRight
            text: qsTr("%1 channel(s)").arg(channelsCount)
        }
    }
}
