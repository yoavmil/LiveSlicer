#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QDebug>

#define DBGF qDebug() << __FUNCTION__ <<':' <<__LINE__
#define WRNF qWarning() << __FUNCTION__ <<':' <<__LINE__

class Logger
{
public:
    Logger();
    ~Logger();
};

#endif // LOGGER_H
