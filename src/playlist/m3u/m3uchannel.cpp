#include "m3uchannel.h"

M3UChannel::M3UChannel(const QString &name, const QUrl url, const QString &logo, QObject *parent) : QObject(parent), _name(name), _logo(logo), _url(url)
{

}

M3UChannel::M3UChannel(const QString &name, const QUrl url, QObject *parent): QObject(parent), _name(name), _url(url)
{

}

const QString &M3UChannel::name() const
{
    return this->_name;
}

const QString &M3UChannel::logo() const
{
    return this->_logo;
}

const QUrl &M3UChannel::url() const
{
    return this->_url;
}

void M3UChannel::setName(const QString &v)
{
    if(this->_name == v)
        return;

    this->_name = v;
    emit nameChanged();
}

void M3UChannel::setLogo(const QString &v)
{
    if(this->_logo == v)
        return;

    this->_logo = v;
    emit logoChanged();
}

void M3UChannel::setUrl(const QUrl &v)
{
    if(this->_url == v)
        return;

    this->_url = v;
    emit urlChanged();
}

