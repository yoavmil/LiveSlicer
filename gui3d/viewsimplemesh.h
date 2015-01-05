#ifndef VIEWMESH_H
#define VIEWMESH_H

#include <QObject>
#include <QColor>
#include <QVector>

#include "common.h"
#include "viewitem.h"
#include "aabb3d.h"

class ViewSimpleMesh : public ViewItem
{
    Q_OBJECT

public:
    explicit ViewSimpleMesh(QObject *parent = 0);
    ~ViewSimpleMesh();
    QColor Color;

    // ViewItem interface
    void SetFacets(QVector<StlFacet> _facets);// {facets = _facets;}

protected:
    virtual void doPaint() Q_DECL_OVERRIDE;

signals:

public slots:

private:
    QVector<StlFacet> facets;
    AABB3D aabb;
    QVector3D originalCenter;

    void updateAABB();
    void centralize();

};

#endif // VIEWMESH_H
