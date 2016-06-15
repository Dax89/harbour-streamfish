#ifndef M3UPARSER_H
#define M3UPARSER_H

#include <QObject>
#include <QString>
#include "m3uchannel.h"

class M3UParser: public QObject
{
    Q_OBJECT

    public:
        M3UParser(QObject* parent = 0);
        const QString& lastError() const;
        bool parse(const QString& m3udata, QList<M3UChannel*>& channels, QObject *owner);

    private:
        bool error(const QString& errmsg);
        void warning(const QString& errmsg, int line, bool &extinfdone);

    private:
        QString _lasterror;
};

#endif // M3UPARSER_H
