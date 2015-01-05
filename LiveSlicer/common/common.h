#ifndef COMMON
#define COMMON


//stl format stuff
#define STL_BINARY_HEADER_SIZE            84
typedef char stl_extra[2];
typedef struct
{
  float normal[3];
  float coords[3][3];
  stl_extra  extra;
} StlFacet;
#define SIZEOF_STL_FACET       50

#define PI 3.141592653589793238462

#endif // COMMON

