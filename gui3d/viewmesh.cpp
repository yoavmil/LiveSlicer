#include "viewmesh.h"
#include "logger.h"
#include "mesh.h"

ViewMesh::ViewMesh(Mesh *_mesh):
    mesh(_mesh),
    dataCreated(false)
{
    //TODO connect here to stuff, maybe delete later stuff
}

ViewMesh::~ViewMesh()
{

}

void ViewMesh::doPaint()
{
    if (!dataCreated)
        initData();

    if (failedToLoad)
        return;

    vao.bind();
//    gl->glDrawElements(GL_TRIANGLES, mesh->facets.size()*3, GL_UNSIGNED_SHORT, 0);
    vao.release();

}

void ViewMesh::initData()
{
    dataCreated = true;
    failedToLoad = true;
    if (mesh->facets.size() == 0)
        return;

    vao.create();
    vao.bind();

    vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    if (!vertexBuffer.create()){
        return;
    }

    vertexBuffer.bind();

    gl->glBufferData(vertexBuffer.type(), mesh->facets.size()*sizeof(GLFacetData),
            mesh->facets.data(), GL_STATIC_DRAW);

    //gl->glBufferData(indexBuffer.type(), sizeof(indices), indices, GL_STATIC_DRAW);

    vertexBuffer.release();
    failedToLoad = false;

    vao.release();
}
