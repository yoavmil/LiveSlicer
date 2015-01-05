#include "aabb3d.h"

AABB3D::AABB3D():
    empty(true)
{

}

AABB3D::~AABB3D()
{

}

void AABB3D::Add(const QVector3D &p)
{
    min.setX(std::min(min.x(), p.x()));
    min.setY(std::min(min.y(), p.y()));
    min.setZ(std::min(min.z(), p.z()));

    max.setX(std::max(max.x(), p.x()));
    max.setY(std::max(max.y(), p.y()));
    max.setZ(std::max(max.z(), p.z()));

    if (empty)
        empty = false;
}

void AABB3D::Add(const AABB3D &other)
{
    Add(other.Min());
    Add(other.Max());
}

bool AABB3D::IsInside(const QVector3D &p) const
{
    return lessOrEqaul(Min(), p) && lessOrEqaul(p, Max());
}

bool AABB3D::IsInside(const AABB3D &other) const
{
    return IsInside(other.Min()) && IsInside(other.Max());
}

QVector3D AABB3D::Center() const
{
    return (min + max)/2;
}

void AABB3D::Clear()
{
    empty = true;
}

bool AABB3D::lessOrEqaul(const QVector3D &a, const QVector3D &b)
{
    return a.x() <= b.x() && a.y() <= b.y() && a.z() <= b.z();
}



