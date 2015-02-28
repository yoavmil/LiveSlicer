#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <vector>
#include <QGL>

#include "vertexdata.h"
#include "common.h"

struct MeshStats {
    int origNrFacets;
    //TODO add here stuff;
};

class Mesh : public QObject
{
    Q_OBJECT

public:
    explicit Mesh();
    ~Mesh();
    std::vector<GLFacetData> facets;//triplets
    MeshStats meshStats;

signals:

public slots:

};

#endif // MESH_H
