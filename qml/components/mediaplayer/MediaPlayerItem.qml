import QtQuick 2.1

Item
{
    function keepVisible(keep) {
        if(!keep) {
            timerdissolve.restart();
            return;
        }

        timerdissolve.stop()
        mediaplayeritem.opacity = 1.0;
    }

    function restoreOpacity() {
        mediaplayeritem.opacity = 1.0;
        timerdissolve.restart();
    }

    id: mediaplayeritem
    visible: (opacity > 0.0) && (Qt.application.state === Qt.ApplicationActive)
    z: 10

    Behavior on opacity { NumberAnimation { duration: 800; easing.type: Easing.Linear } }

    Timer
    {
        id: timerdissolve
        interval: 2000

        onTriggered: {
            mediaplayeritem.opacity = 0.0;
        }
    }
}

