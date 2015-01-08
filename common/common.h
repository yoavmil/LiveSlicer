#ifndef COMMON
#define COMMON

#include <glm/glm.hpp>

//stl format stuff
#define STL_BINARY_HEADER_SIZE            84
typedef char stl_extra[2];
typedef struct
{
  glm::vec3 normal;
  glm::vec3 vertices[3];
  stl_extra  extra;
} StlFacet;
#define SIZEOF_STL_FACET       50

#define PI 3.141592653589793238462

#endif // COMMON

