#ifndef BBOX_H
#define BBOX_H

#include "glm/vec3.hpp"

class BBox
{
public:
    BBox();
    void Include(glm::vec3 vec);
    void Include(const BBox& other);
    const glm::vec3& Min() { return min; }
    const glm::vec3& Max() { return max; }

private:
    glm::vec3 min, max;
};

#endif // BBOX_H
