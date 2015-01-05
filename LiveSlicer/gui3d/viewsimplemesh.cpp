#include "viewsimplemesh.h"
#include "logger.h"

ViewSimpleMesh::ViewSimpleMesh(QObject *parent) : ViewItem(parent)
{
    Color = Qt::magenta;
}

ViewSimpleMesh::~ViewSimpleMesh()
{

}

void ViewSimpleMesh::SetFacets(QVector<StlFacet> _facets)
{
    facets = _facets;
    updateAABB();
    centralize();
}

void ViewSimpleMesh::doPaint()
{
    if (Color.alpha() == 255)
        glColor3b(Color.red(), Color.green(), Color.blue());
    else
        glColor4b(Color.red(), Color.green(), Color.blue(), Color.alpha());

    glBegin(GL_TRIANGLES);
    for(const StlFacet& f: facets)
    {
        glNormal3fv(f.normal);
        for (int v = 0; v < 3; v++) {
            glColor3fv(f.normal);
            glVertex3fv(f.coords[v]);
        }
    }
    glEnd();
}

void ViewSimpleMesh::updateAABB()
{
    for(const StlFacet& f: facets)
    {
        for (int i = 0; i < 3; i++) {
            aabb.Add(QVector3D(f.coords[i][0], f.coords[i][1], f.coords[i][2]));
        }
    }
}

void ViewSimpleMesh::centralize()
{
    originalCenter = aabb.Center();
    for(StlFacet& f: facets)
    {
        for (int i = 0; i < 3; i++) {
            f.coords[i][0] -= originalCenter.x();
            f.coords[i][1] -= originalCenter.y();
            f.coords[i][2] -= originalCenter.z();
        }
    }
}
