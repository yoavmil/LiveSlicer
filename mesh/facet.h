#ifndef FACET_H
#define FACET_H

#include <QList>

class Mesh;

class Facet
{
public:
    Facet();
    ~Facet();

    long v[3];//vertex index
    long n;//normal index
    QList<Facet*> Neighbors;
    Mesh* mesh;
};

#endif // FACET_H
