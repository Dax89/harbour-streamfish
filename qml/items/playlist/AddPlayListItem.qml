import QtQuick 2.1
import Sailfish.Silica 1.0
import "../../components"

Row
{
    property alias text: tfurl.text
    property alias invalidUrl: tfurl.errorHighlight
    property bool hideClose: false

    signal textCommited()
    signal removeRequested()

    id: addplaylistitem

    TextField
    {
        id: tfurl
        labelVisible: false
        placeholderText: qsTr("Playlist Url")
        onTextChanged: textCommited()

        width: {
            var w = parent.width;

            if(imgclose.visible)
                w -= imgclose.width;

            if(imgpaste.visible)
                w -= imgpaste.width;
        }
    }

    ImageButton
    {
        id: imgpaste
        source: "image://theme/icon-m-clipboard"
        width: parent.height
        height: parent.height

        onClicked: {
            tfurl.text = Clipboard.text;
        }
    }

    ImageButton
    {
        id: imgclose
        visible: !hideClose
        source: "image://theme/icon-m-clear"
        width: parent.height
        height: parent.height
        onClicked: removeRequested()
    }
}

