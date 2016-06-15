#include <QtQuick>
#include <sailfishapp.h>
#include "playlist/m3u/m3uchannel.h"
#include "playlist/playlistmanager.h"
#include "model/m3uplaylistsmodel.h"
#include "model/m3uchannelsmodel.h"
#include "model/m3ufilteredchannelsmodel.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    application->setApplicationName("harbour-streamfish");

    qmlRegisterUncreatableType<M3UChannel>("harbour.streamfish.Model", 1, 0, "M3UChannel", "");
    qmlRegisterUncreatableType<M3UPlayList>("harbour.streamfish.Model", 1, 0, "M3UPlayList", "");
    qmlRegisterType<M3UPlayListsModel>("harbour.streamfish.Model", 1, 0, "M3UPlayListsModel");
    qmlRegisterType<M3UFilteredChannelsModel>("harbour.streamfish.Model", 1, 0, "M3UFilteredChannelsModel");
    qmlRegisterType<M3UChannelsModel>("harbour.streamfish.Model", 1, 0, "M3UChannelsModel");
    qmlRegisterType<PlayListManager>("harbour.streamfish.PlayList", 1, 0, "PlayListManager");

    QScopedPointer<QQuickView> view(SailfishApp::createView());
    view->setSource(SailfishApp::pathTo("qml/harbour-streamfish.qml"));
    view->show();

    return application->exec();
}

