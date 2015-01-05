#ifndef AABB3D_H
#define AABB3D_H

#include <QVector3D>
/**
 * @brief The AABB3D class
 * axis aligned bounding box
 */
class AABB3D
{
public:
    AABB3D();
    ~AABB3D();
    const QVector3D& Min() const {return min;}
    const QVector3D& Max() const {return max;}
    bool Empty() const;
    void Add(const QVector3D& p);
    void Add(const AABB3D& other);
    bool IsInside(const QVector3D& p) const;//on the border is 'inside'
    bool IsInside(const AABB3D& other) const;
    //bool Intersects(const AABB3D& other) const;
    QVector3D Center() const;
    void Clear();

private:
    QVector3D min,max;
    bool empty;

    static bool lessOrEqaul(const QVector3D& a, const QVector3D& b);
};

#endif // AABB3D_H
