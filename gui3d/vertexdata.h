#ifndef VERTEXDATA
#define VERTEXDATA

#include <vector>
#include <glm/glm.hpp>

struct GLVertexData
{
    glm::vec3 coord;
    glm::vec3 normal;
    glm::vec3 color;
};

struct GLFacetData
{
    GLVertexData vertices[3];
};

#endif // VERTEXDATA

