#include "bbox.h"
#include <limits>
#include <algorithm>

BBox::BBox()
{
    min.x = min.y = min.z = std::numeric_limits<float>::max();
    max.x = max.y = max.z = std::numeric_limits<float>::min();
}

void BBox::Include(glm::vec3 vec)
{
    min.x = std::min(min.x, vec.x);
    min.y = std::min(min.y, vec.y);
    min.z = std::min(min.z, vec.z);
    max.x = std::max(max.x, vec.x);
    max.y = std::max(max.y, vec.y);
    max.z = std::max(max.z, vec.z);
}

void BBox::Include(const BBox &other)
{
    Include(other.min);
    Include(other.max);
}

