#include "utils.h"
#include "glm/gtx/normalize_dot.hpp"
QDebug operator<< (QDebug d, const glm::vec2 &v) {
    d << qPrintable(QString("[%1,%2]").arg(v.x).arg(v.y));
    return d;
}

QDebug operator<< (QDebug d, const glm::vec3 &v) {
    d << qPrintable(QString("[%1,%2,%3]").arg(v.x).arg(v.y).arg(v.z));
    return d;
}

QDebug operator<<(QDebug d, const glm::vec4 &v)
{
    d << qPrintable(QString("[%1,%2,%3,%4]").arg(v.x).arg(v.y).arg(v.z).arg(v.w));
    return d;
}

QDebug operator<< (QDebug d, const LineDirLess &line) {
    d << line.v0 << "-" << line.v1;
    return d;
}

QDebug operator<<(QDebug d, const glm::mat4x4 &mat)
{
    d << mat[0] << '\n' <<
                   mat[1] << '\n' <<
                   mat[2] << '\n' <<
                   mat[3];
    return d;
}

bool operator==(const glm::vec3 &v1, const glm::vec3 &v2)
{
    return  v1.x == v2.x &&
            v1.y == v2.y &&
            v1.z == v2.z;
}

bool operator==(const LineDirLess &l1, const LineDirLess &l2)
{
    return  (l1.v0 == l2.v0 && l1.v1 == l2.v1) ||
            (l1.v0 == l2.v1 && l1.v1 == l2.v0);
}


std::size_t std::hashFloat(const float &f) {
    if (f == 0.0f) return 0;
    return _Hash_impl::hash(f);
}


std::size_t std::hashVec3(const glm::vec3 &vec) {
    return hashFloat(vec.x) ^ hashFloat(vec.y + 1) ^ hashFloat(vec.z + 2);
}


std::size_t std::hash<glm::vec3>::operator()(const glm::vec3 &vec) const
{
    return hashVec3(vec);
}


std::size_t std::hash<LineDirLess>::operator()(const LineDirLess &l) const
{
    return hashVec3(l.v0) ^ hashVec3(l.v1);
}


glm::vec3 computeNormal(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c) {
    return glm::fastNormalize(glm::cross(c - a, b - a));
}
