#ifndef FACET_H
#define FACET_H

#include <QList>

class SharedVertex;
class Mesh;
class QVector3D;

class Facet
{
public:
    Facet();
    ~Facet();

    SharedVertex* v[3];
    QVector3D* n;
    QList<Facet*> Neighbors;
    Mesh* mesh;
};

#endif // FACET_H
