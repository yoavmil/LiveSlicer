#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : private QSettings
{

public:

    static QString LastMeshDir();
    static void LastMeshDir(const QString& dir);

private:
    static void setValue(const QString &key, const QVariant &value);
    static QVariant value(const QString &key, const QVariant &defaultValue = QVariant());

    Settings();
    ~Settings();
};

#endif // SETTINGS_H
