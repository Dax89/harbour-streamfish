#include "m3uparser.h"
#include <QRegularExpression>
#include <QStringList>
#include <QDebug>

M3UParser::M3UParser(QObject *parent): QObject(parent)
{

}

const QString &M3UParser::lastError() const
{
    return this->_lasterror;
}

bool M3UParser::parse(const QString &m3udata, QList<M3UChannel *> &channels, QObject* owner)
{
    QStringList lines = m3udata.split(QRegularExpression("[\r\n]"), QString::SkipEmptyParts);
    QRegularExpression channelnamergx("#EXTINF:[^,]+?,(.+)");
    QRegularExpression channellogorgx("tvg-logo=\"([^\"]+)\"");
    bool extinfdone = false;

    for(int i = 0 ; i < lines.length(); i++)
    {
        QString line = lines[i].trimmed();

        if(line == "#EXTM3U") // Skip header, if any
            continue;

        if(line.startsWith("#EXTINF"))
        {
            if(extinfdone)
            {
                this->warning(tr("Malformed M3U playlist, skipping line %1"), i, extinfdone);
                continue;
            }

            QRegularExpressionMatch m1 = channelnamergx.match(line);
            QRegularExpressionMatch m2 = channellogorgx.match(line);
            channels.append(new M3UChannel(m1.captured(1), QString(), m2.captured(1), owner));
            extinfdone = true;
        }
        else
        {
            if(line.startsWith("#"))
                continue;

            if(!extinfdone)
            {
                this->warning(tr("Malformed M3U playlist, skipping line %1"), i, extinfdone);
                continue;
            }

            channels.last()->setUrl(line);
            extinfdone = false;
        }
    }

    if(channels.isEmpty())
        return this->error(tr("Invalid M3U playlist"));

    return true;
}

bool M3UParser::error(const QString &errmsg)
{
    this->_lasterror = errmsg;
    return false;
}

void M3UParser::warning(const QString &errmsg, int line, bool& extinfdone)
{
    qWarning() << QString(errmsg).arg(line);
    extinfdone = !extinfdone;
}
