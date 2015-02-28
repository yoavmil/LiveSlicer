#ifndef QTHELPERS
#define QTHELPERS

#include <QString>
#include <QFile>
#include <string>

std::string FileToString(const char* path) {
    QFile f(path);
    if (!f.open(QFile::ReadOnly)) {
        return "";
    }
    return(f.readAll().data());
}

QString FromStdString(const std::string& s) {
    return QString(s.data());
}

#endif // QTHELPERS

