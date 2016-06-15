#ifndef M3UCHANNEL_H
#define M3UCHANNEL_H

#include <QObject>
#include <QString>
#include <QUrl>

class M3UChannel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString logo READ logo WRITE setLogo NOTIFY logoChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)

    public:
        explicit M3UChannel(const QString& name, const QUrl url, const QString& logo, QObject *parent = 0);
        explicit M3UChannel(const QString& name, const QUrl url, QObject *parent = 0);
        const QString& name() const;
        const QString& logo() const;
        const QUrl& url() const;
        void setName(const QString& v);
        void setLogo(const QString& v);
        void setUrl(const QUrl& v);

    signals:
        void nameChanged();
        void logoChanged();
        void urlChanged();

    private:
        QString _name;
        QString _logo;
        QUrl _url;
};

Q_DECLARE_METATYPE(M3UChannel*)

#endif // M3UCHANNEL_H
