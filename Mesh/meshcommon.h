#ifndef MESHCOMMON
#define MESHCOMMON

#include <QList>
#include <glm/vec3.hpp>

class MeshFacet {
public:
    int vertexIdx[3];
    QList<int> neighborsIdx;
    enum MeshFacetFlags
    {
        Valid,
        NoArea,
        NoNeighbors,
    };
    MeshFacetFlags flags;
    MeshFacet() {
        vertexIdx[0] = vertexIdx[1] = vertexIdx[2] = -1;
        flags = Valid;
    }
};

//stl format stuff
#define STL_BINARY_HEADER_SIZE            84
#define SIZEOF_STL_FACET                  50
typedef char stl_extra[2];
struct StlFacet
{
  glm::vec3 normal;
  glm::vec3 vertices[3];
  stl_extra  extra;
};

struct MeshGLVertex {
    glm::vec3 vertex, rgb, normal;
};

#endif // MESHCOMMON

