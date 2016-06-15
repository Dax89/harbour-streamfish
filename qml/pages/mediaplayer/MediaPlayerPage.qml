import QtQuick 2.1
import QtMultimedia 5.0
import Sailfish.Silica 1.0
import "../../components/mediaplayer"

Page
{
    readonly property bool playerActive: true
    property var channel

    id: mediaplayerpage
    allowedOrientations : Orientation.Landscape | Orientation.LandscapeInverted

    states: [ State { name: "error"
                      PropertyChanges { target: mperror; showError: true }
                      PropertyChanges { target: pcbusy; visible: false } },

              State { name: "loading"
                      PropertyChanges { target: mperror; showError: false }
                      PropertyChanges { target: pcbusy; visible: true } },

              State { name: "playing"
                      PropertyChanges { target: mperror; showError: false }
                      PropertyChanges { target: pcbusy; visible: false } }]

    onStateChanged: {
        //if((state === "") || (state === "error"))
            //mptoolbar.keepVisible(true);
    }

    Video
    {
        id: video
        anchors.fill: parent
        source: channel.url
        autoPlay: false

        onStatusChanged: {
            if((playbackState !== MediaPlayer.PlayingState) && ((status === MediaPlayer.Loading) || (status === MediaPlayer.Stalled)))
                mediaplayerpage.state = "loading";
            else if(status === MediaPlayer.Loaded)
                video.play();
        }

        onPlaybackStateChanged: {
            var keep = video.playbackState !== MediaPlayer.PlayingState;

            //mptoolbar.keepVisible(keep);
            mptitle.keepVisible(keep);

            if(video.playbackState === MediaPlayer.PlayingState)
                mediaplayerpage.state = "playing";
        }

        onErrorChanged: {
            if(video.error === MediaPlayer.NoError)
                return;

            mediaplayerpage.state = "error";
            video.stop(); // Avoid MediaPlayer undefined behavior
        }

        BusyIndicator { id: pcbusy; anchors.centerIn: parent; visible: false; running: visible; size: BusyIndicatorSize.Large; z: 15 }

        MediaPlayerTitle
        {
            id: mptitle
            title: channel.name
            anchors { left: parent.left; top: parent.top; right: parent.right; leftMargin: Theme.paddingMedium; topMargin: Theme.paddingMedium; rightMargin: Theme.paddingMedium }
        }

        MediaPlayerPopup { id: mppopup; anchors.centerIn: parent }

        MouseArea
        {
            anchors.fill: parent

            onClicked: {
                if(mptitle.opacity < 1.0) {
                    mptitle.restoreOpacity();
                    return;
                }

                if(video.playbackState === MediaPlayer.PlayingState) {
                    video.pause();
                    mppopup.animatePause();
                }
                else if(video.playbackState === MediaPlayer.PausedState) {
                    video.play();
                    mppopup.animatePlay();
                }
            }
        }

        MediaPlayerError { id: mperror; anchors.fill: parent; errorMessage: video.errorString }
    }

    CoverActionList /* Media Player Cover Actions */
    {
        enabled: (mediaplayerpage.state !== "error")
        iconBackground: true

        CoverAction
        {
            iconSource: video.playbackState === MediaPlayer.PlayingState ? "image://theme/icon-cover-pause" : "image://theme/icon-cover-play"
            onTriggered: video.playbackState === MediaPlayer.PlayingState ? video.pause() : video.play();
        }

        CoverAction
        {
            iconSource: "image://theme/icon-cover-cancel"
            onTriggered: pageStack.pop()
        }
    }

    CoverActionList /* Media Player Fallback Cover Actions */
    {
        enabled: (mediaplayerpage.state === "error")
        iconBackground: true

        CoverAction
        {
            iconSource: "image://theme/icon-cover-cancel"
            onTriggered: pageStack.pop()
        }
    }
}
