import QtQuick 2.1
import Sailfish.Silica 1.0
import "pages/playlist"
import "models"

ApplicationWindow
{
    readonly property Context context: context

    Context
    {
        id: context
        Component.onCompleted: context.manager.load()
    }

    id: mainwindow
    allowedOrientations: Orientation.All
    _defaultPageOrientations: Orientation.All
    initialPage: Component { PlaylistsPage { } }

    cover: {
        if(pageStack.currentPage.playerActive !== true)
            return Qt.resolvedUrl("cover/CoverPage.qml");

        return undefined;
    }
}
