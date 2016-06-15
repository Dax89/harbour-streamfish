import QtQuick 2.1
import Sailfish.Silica 1.0
import "../../js/UrlHelper.js" as UrlHelper

Item
{
    property string logoUrl
    property real contentWidth

    readonly property string channelNumber: {
        var cap = /([0-9]+)\.png/.exec(logoUrl)

        if(!cap || !cap[1])
            return "";

        return cap[1];
    }

    width: {
        if(imgfallback.visible)
            return imgfallback.width;

        return contentWidth;
    }

    Image
    {
        id: imglogo
        asynchronous: true
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        visible: (status === Image.Ready)

        source: {
            if(channelNumber.length > 0)
                return "";

            if(UrlHelper.isUrl(logoUrl))
                return logoUrl;

            return "qrc:///res/channel.png";
        }

        onStatusChanged: {
            if(status !== Image.Error)
                return;

            return "qrc:///res/channel.png";
        }
    }

    Rectangle
    {
        id: imgfallback
        color: Theme.secondaryHighlightColor
        height: parent.height + Theme.paddingMedium
        width: visible ? lblchannelnumber.contentWidth + Theme.paddingMedium : 0
        radius: width * 0.5
        visible: !imglogo.visible

        Label
        {
            id: lblchannelnumber
            anchors.centerIn: parent
            font { pixelSize: Theme.fontSizeTiny; bold: true }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: Theme.primaryColor
            text: channelNumber
        }
    }
}

