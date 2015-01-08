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
    return;
    if (Color.alpha() == 255)
        glColor3b(Color.red(), Color.green(), Color.blue());
    else
        glColor4b(Color.red(), Color.green(), Color.blue(), Color.alpha());

    glBegin(GL_TRIANGLES);
    for(const StlFacet& f: facets)
    {
        glNormal3fv(&f.normal[0]);
        for (int v = 0; v < 3; v++) {
            glColor3fv(&f.normal[0]);
            glVertex3fv(&f.vertices[v][0]);
        }
    }
    glEnd();
}

void ViewSimpleMesh::updateAABB()
{
    for(const StlFacet& f: facets)
    {
        for (int i = 0; i < 3; i++) {
            aabb.Add(QVector3D(f.vertices[i][0], f.vertices[i][1], f.vertices[i][2]));
        }
    }
}

void ViewSimpleMesh::centralize()
{
    originalCenter = aabb.Center();
    for(StlFacet& f: facets)
    {
        for (int i = 0; i < 3; i++) {
            f.vertices[i][0] -= originalCenter.x();
            f.vertices[i][1] -= originalCenter.y();
            f.vertices[i][2] -= originalCenter.z();
        }
    }
}
