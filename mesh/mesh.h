#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <QVector3D>
#include <QVector>

#include "facet.h"
#include "sharedvertex.h"
class Mesh : public QObject
{
    Q_OBJECT
public:
    explicit Mesh(QObject *parent = 0);
    ~Mesh();

    QVector<SharedVertex> vertices;
    QVector<Facet> facets;

signals:

public slots:



};

#endif // MESH_H
