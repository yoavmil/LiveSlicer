#include "settings.h"
#include "utils.h"
#include <QStandardPaths>

QString Settings::LastMeshDir()
{
    return value(__FUNCTION__, QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).first()).toString();
}

void Settings::LastMeshDir(const QString &dir)
{
    setValue(__FUNCTION__, dir);
}

void Settings::setValue(const QString &key, const QVariant &value)
{
    QSettings().QSettings::setValue(key, value);
}

QVariant Settings::value(const QString &key, const QVariant &defaultValue)
{
    return Settings().QSettings::value(key, defaultValue);
}

Settings::Settings() :
    QSettings(QStandardPaths::standardLocations(QStandardPaths::DataLocation).first(), QSettings::IniFormat)
{}

Settings::~Settings()
{
    sync();
}
