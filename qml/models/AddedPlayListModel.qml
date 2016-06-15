import QtQuick 2.1

Item
{
    property alias count: listmodel.count
    property alias model: listmodel
    property bool acceptable: false

    function more() {
        listmodel.append({ "url": "" });
    }

    function remove(index) {
        listmodel.remove(index);
    }

    function commit(index, url) {
        listmodel.setProperty(index, "url", url);
        timcheckacceptable.restart();
    }

    function isUrl(url) {
        return listmodel.urlregex.test(url) || listmodel.ipregex.test(url) || listmodel.ipportregex.test(url) || listmodel.hostportregex.test(url);
    }

    function forEach(callback) {
        for(var i = 0; i < listmodel.count; i++)
            callback(listmodel.get(i).url);
    }

    id: addedplaylistmodel
    Component.onCompleted: more()

    Timer
    {
        id: timcheckacceptable
        interval: 800
        onTriggered: listmodel.checkAcceptable()
    }

    ListModel
    {
        readonly property var urlregex: new RegExp("[-a-zA-Z0-9@:%._\\+~#=]{1,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%_\\+.~#?&//=]*)");
        readonly property var ipregex: new RegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
        readonly property var ipportregex: new RegExp("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}:[0-9]+");
        readonly property var hostportregex: new RegExp("[-a-zA-Z0-9@:%._\\+~#=]{1,256}:[0-9]+");

        id: listmodel

        function checkAcceptable() {
            for(var i = 0; i < listmodel.count; i++) {
                var obj = get(i);

                if(obj.url.length <= 0) {
                    acceptable = false;
                    return;
                }
            }

            acceptable = true;
        }
    }
}
