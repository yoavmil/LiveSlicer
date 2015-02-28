#include "viewworld.h"
#include <QOpenGLVertexArrayObject>
#include "logger.h"
#include "viewer3d.h"

ViewWorld::ViewWorld(QObject *parent):
    ViewItem(parent)
{
    vboId[0] = 0;
}

ViewWorld::~ViewWorld()
{
    vao.destroy();
}

void ViewWorld::doPaint()
{
    if (!vao.isCreated())
        return;

    vao.bind();
    glDrawArrays(GL_QUADS, 0, 1);
    vao.release();
}


void ViewWorld::InitGL(Viewer3D* _viewer)
{
    ViewItem::InitGL(_viewer);

    if (!vao.isCreated()) {
        if (!vao.create()) {
            DBGF << "failed to vreate vao";
            return;
        }

        vao.bind();

        gl->glGenBuffers(1, vboId);
        gl->glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
        GLfloat vertices[] = {
            0, 0, 0,
            0, 200, 0,
            200, 200, 0,
            200, 0, 0
        };
        gl->glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        vao.release();
        initiated = true;
    }

    /* from https://www.youtube.com/watch?v=Dyue3MzJDss&index=5&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY
     * glGenBuffers()
     * glBindBuffer()//bind
     * glBufferData()//copy the data
     * glEnableVertexAttribArray(id0)//enable sending it through the pipeline
     * glVertexAttribPointer(id0, how many, type, normalize?,
     *      stride=offset bewteen datas,
     *      offset from beggining);//tell opengl what this data is
     * glEnableVertexAttribArray(id1);//1 is for another id
     *
     */   
}
