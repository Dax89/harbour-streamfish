import QtQuick 2.1
import Sailfish.Silica 1.0

CoverBackground
{
    id: coverpage

    Label
    {
        id: label
        anchors.centerIn: parent
        text: qsTr("My Cover")
    }

    CoverActionList
    {
        id: coveraction

        CoverAction {
            iconSource: "image://theme/icon-cover-next"
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-pause"
        }
    }
}


