#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <vector>

#include <glm/glm.hpp>

#include "facet.h"
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

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> facetNormals;
    std::vector<Facet> facets;

    MeshStats meshStats;

signals:

public slots:

};

#endif // MESH_H
