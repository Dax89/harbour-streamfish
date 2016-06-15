#ifndef M3UPLAYLIST_H
#define M3UPLAYLIST_H

#include <QObject>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "m3uparser.h"

class M3UPlayList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name CONSTANT FINAL)
    Q_PROPERTY(int channelsCount READ channelsCount NOTIFY channelsCountChanged)

    public:
        explicit M3UPlayList(const QString& name, const QUrl& url, QObject *parent = 0);
        explicit M3UPlayList(const QString& name, const QUrl& url, const QString& file, int count, QObject *parent = 0);
        const QString& name() const;
        const QString& file() const;
        const QUrl& url() const;
        int channelsCount() const;
        M3UChannel* channelAt(int i) const;
        QNetworkAccessManager* networkManager();
        void save(const QString& dest);
        void load(bool force = false);
        void download();

    private slots:
        void onDownloadFinished();
        void onDownloadError(QNetworkReply::NetworkError);

    signals:
        void loaded();
        void error(const QString& errmsg);
        void channelsCountChanged();

    private:
        bool _loaded;
        int _count;
        QList<M3UChannel*> _channels;
        QString _name;
        QString _file;
        QUrl _url;

    private:
        static QNetworkAccessManager* _netmgr;
        static const QString VERSION;
};

Q_DECLARE_METATYPE(M3UPlayList*)

#endif // M3UPLAYLIST_H
