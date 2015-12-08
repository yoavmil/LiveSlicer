#ifndef UTILS
#define UTILS

#include <QDebug>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

//a line with no direction, ex. v0 and v1 is unordered
struct LineDirLess {
    glm::vec3 v0, v1;
};

namespace std {
size_t hashFloat(const float& f);
size_t hashVec3(const glm::vec3& vec);

template <> struct hash<glm::vec3>
{
    size_t operator()(const glm::vec3 & vec) const;
};
template <> struct hash<LineDirLess>
{
    size_t operator()(const LineDirLess & l) const;
};
}

#define DBGF qDebug() << __FUNCTION__ <<':' <<__LINE__
#define WRNF qWarning() << __FUNCTION__ <<':' <<__LINE__
#define _S(x) qPrintable(QString("%1=%2").arg(#x).arg(x))

QDebug operator<< (QDebug d, const glm::vec2 &v);
QDebug operator<< (QDebug d, const glm::vec3 &v);
QDebug operator<< (QDebug d, const glm::vec4 &v);
QDebug operator<< (QDebug d, const glm::mat4x4 &mat);

bool operator==(const glm::vec3 &e1, const glm::vec3 &e2);
bool operator==(const LineDirLess &e1, const LineDirLess &e2);

glm::vec3 computeNormal(glm::vec3 const & a, glm::vec3 const & b, glm::vec3 const & c);

#endif // UTILS

