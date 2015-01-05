#ifndef SHAREDVERTEX_H
#define SHAREDVERTEX_H

#include <QObject>
#include <QVector3D>

class SharedVertex : public QObject, public QVector3D
{
        Q_OBJECT
public:
    explicit SharedVertex(QObject *parent = 0);
    ~SharedVertex();

signals:
    void moved(QVector3D from, QVector3D to);
};

#endif // SHAREDVERTEX_H
