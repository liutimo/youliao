#include "yllocalsettings.h"

#include <QSettings>

YLLocalSettings* YLLocalSettings::m_instance = Q_NULLPTR;

YLLocalSettings::YLLocalSettings(QObject *parent) : QObject(parent)
{
    m_settings  = new QSettings("youliao.ini", QSettings::IniFormat);
}

YLLocalSettings* YLLocalSettings::instance()
{
    if (m_instance == Q_NULLPTR)
        m_instance = new YLLocalSettings;

    return m_instance;
}

void YLLocalSettings::beginGroup(const QString &prefix)
{
    m_settings->beginGroup(prefix);
}

void YLLocalSettings::endGroup()
{
    m_settings->endGroup();
}

void YLLocalSettings::setValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

QVariant YLLocalSettings::getValue(const QString &key)
{
    return m_settings->value(key);
}

int YLLocalSettings::getInt(const QString &key)
{
    return getValue(key).toInt();
}

bool YLLocalSettings::getBool(const QString &key)
{
    return getValue(key).toBool();
}
