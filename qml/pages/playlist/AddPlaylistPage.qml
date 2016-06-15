import QtQuick 2.1
import Sailfish.Silica 1.0
import harbour.streamfish.PlayList 1.0
import "../../models"
import "../../components"
import "../../js/UrlHelper.js" as UrlHelper

Dialog
{
    property Context context

    id: addplaylistpage
    canAccept: (tfname.text.length > 0) && UrlHelper.isUrl(tfurl.text)
    onAccepted: context.manager.add(tfname.text, tfurl.text)

    SilicaFlickable
    {
        id: flickable
        anchors.fill: parent
        contentHeight: content.height

        Column
        {
            id: content
            width: parent.width

            DialogHeader {
                acceptText: qsTr("Add")
            }

            TextField
            {
                id: tfname
                width: parent.width
                placeholderText: qsTr("Name")
            }

            Row
            {
                width: parent.width
                height: Theme.itemSizeSmall

                TextField
                {
                    id: tfurl
                    width: parent.width - imgpaste.width
                    labelVisible: false
                    placeholderText: qsTr("Url")
                    inputMethodHints: Qt.ImhUrlCharactersOnly
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
            }
        }
    }
}

