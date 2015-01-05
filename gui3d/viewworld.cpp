#include "viewworld.h"
#include <QOpenGLVertexArrayObject>
#include "logger.h"

ViewWorld::ViewWorld(QObject *parent):
    ViewItem(parent),
    vao(nullptr)
{
    
    vboId[0] = 0;
}

ViewWorld::~ViewWorld()
{
    vao->destroy();
}



void ViewWorld::doPaint()
{
    
    if (vao == nullptr)
        return;

    vao->bind();
    glDrawArrays(GL_QUADS, 0, 1);
    vao->release();
}


void ViewWorld::InitGL()
{
    
    if (vao == nullptr) {
        vao = new QOpenGLVertexArrayObject(this);
        if (!vao->create()) {
            vao = nullptr;
            DBGF << "failed to vreate vao";
            return;
        }

        vao->bind();

        gl->glGenBuffers(1, vboId);
        gl->glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
        GLfloat vertices[] = {
            0, 0, 0,
            0, 200, 0,
            200, 200, 0,
            200, 0, 0
        };
        gl->glBufferData(GL_ARRAY_BUFFER, 3*4*sizeof(GLfloat), vertices, GL_STATIC_DRAW);

        vao->release();
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
     * shaders
     * glCreateShader
     * glShaderSource
     * glCompileShader
     *
     * glCreateProgram
     * glLinkProgram
     * glUseProgram
     *
     * the shader:
     * #version 430\r\n
     * in layout(location=0) vec2 position
     * void main()
     * {
     *  gl_Position = vec4(position, 0.0, 1.0)
     * }
     */   
}

const char* vertexShader =
        "#version 430\n\r"
        "in layout(location=0) vec2 pos;" //the input is id0 as vec2 and called 'pos'
        "in layout(location=1) vec3 vColor;"//the input is id1 and callled vColor
        "out vec3 theColor;" //this will be sent the fragment buffer
        "void main(){"
        "   gl_Position = vec4(pos, 0.0, 1.0);"
        "   theColor = vColor;"
        "}";
const char* framgentShader =
        "#version 430\n\r"
        "out vec4 outColor;" //this goes to the screen
        "in vec3 theColor;" //we get this from the vertex shader
        "void main() {"
        "   outColor = vec4(theColor, 1.0);"
        "}";
