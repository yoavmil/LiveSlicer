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
    indexBuffer.bind();
    //vertexBuffer.bind();
    gl->glDrawElements(GL_TRIANGLES, mesh->facets.size()*3, GL_UNSIGNED_SHORT, 0);
    //vertexBuffer.release();
    indexBuffer.release();
}

void ViewMesh::initData()
{
    dataCreated = true;
    failedToLoad = true;
    if (mesh->vertices.size() == 0)
        return;
    if (mesh->facets.size() == 0)
        return;

    vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    if (!vertexBuffer.create()){
        return;
    }

    indexBuffer =  QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    if (!indexBuffer.create()) {
        return;
    }
    vertexBuffer.bind();

    gl->glBufferData(vertexBuffer.type(), mesh->vertices.size()*sizeof(mesh->vertices[0]),
            mesh->vertices.data(), GL_STATIC_DRAW);

    gl->glEnableVertexAttribArray(0);//not sure about this
    gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    GLushort indices[mesh->facets.size()*3];
    for(int i = 0; i < mesh->facets.size(); i++) {
        for (int j = 0; j < 3; j++)
            indices[i*3 + j] = mesh->facets[i].v[j];
    }

    indexBuffer.bind();
    gl->glBufferData(indexBuffer.type(), sizeof(indices), indices, GL_STATIC_DRAW);

    vertexBuffer.release();
    failedToLoad = false;
}
