#ifndef VIEWMESH_H
#define VIEWMESH_H

#include "viewitem.h"

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class Mesh;

class ViewMesh : public ViewItem
{
public:
    ViewMesh(Mesh* _mesh);
    ~ViewMesh();

    // ViewItem interface
protected:
    virtual void doPaint();

    void initData();
    bool dataCreated;
    QOpenGLBuffer vertexBuffer, indexBuffer;
    Mesh* mesh;
    bool failedToLoad;
};

#endif // VIEWMESH_H
