#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "glm/vec3.hpp"

#include "viewer3d.h"
#include "viewerprovider.h"
#include "viewitem.h"
#include "logger.h"
#include "viewercam.h"
#include "vertexdata.h"
#include "qthelpers.h"

void qgluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

Viewer3D::Viewer3D(QWidget *parent):
    QOpenGLWidget(parent),
    provider(nullptr)
{
    viewNeer = 0.1;
    viewFar = 1000;
    backGround = Qt::lightGray;
    cam = new ViewerCam(this);
}

Viewer3D::~Viewer3D()
{
}

void Viewer3D::SetProvider(ViewerProvider *vp)
{
    if (provider != vp) {
        if (provider != nullptr) {
            //tell provider to it is not the provider any more
            //TODO
        }
        provider = vp;
    }
}

void Viewer3D::initializeGL()
{
    initializeOpenGLFunctions();
    initShaders();

    if (provider != nullptr)
        provider->InitGL(this);

    backGround = Qt::lightGray;
    glClearColor(backGround.redF(), backGround.greenF(), backGround.blackF(), backGround.alphaF());   
}

void Viewer3D::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    //setProjectionMat();
}

void Viewer3D::setProjectionMat()
{
    const double aspectRatio = (float) width() / height(), fov = 45.0;
    glMatrixMode(GL_PROJECTION);
    QMatrix4x4 m;
    m.perspective(fov, aspectRatio, viewNeer, viewFar);  /* Znear and Zfar */
    glLoadMatrixf(m.data());
}

void Viewer3D::initShaders()
{

    OpenGLShader vertexShader(FileToString(":/Shaders/simplevertexshader.vsh").data(), ShaderType::Vertex);
    vertexShader.Build();

    OpenGLShader fragShader(FileToString(":/Shaders/simplefragmentshader.frag").data(), ShaderType::Fragment);
    fragShader.Build();
    OpenGLProgram program;
    program.AddShader(vertexShader);
    program.AddShader(fragShader);
    program.Build();
    program.Use();

    vertexLocation = program.AttribLocation("vertex");
    normalLocation = program.AttribLocation("vertexNormal");
    colorLocation = program.AttribLocation("color");
    MVMatLocation = program.UniformLocation("MVmat");
    PMatLocation = program.UniformLocation("Pmat");

    DBGF << vertexLocation;
    DBGF << normalLocation;
    DBGF << colorLocation;
    DBGF << MVMatLocation;
    DBGF << PMatLocation;

    GLFacetData facet;
    facet.vertices[0].coord.x = -1;
    facet.vertices[0].coord.y = -1;
    facet.vertices[0].coord.z = 1;

    facet.vertices[1].coord.x = 0;
    facet.vertices[1].coord.y = 1;
    facet.vertices[1].coord.z = 0;

    facet.vertices[2].coord.x = 1;
    facet.vertices[2].coord.y = 1;
    facet.vertices[2].coord.z = 1;

    facet.vertices[0].color = glm::vec3(1, 0, 0);
    facet.vertices[1].color = glm::vec3(0, 1, 0);
    facet.vertices[2].color = glm::vec3(0, 0, 1);

    glEnableVertexAttribArray(vertexLocation);
    glEnableVertexAttribArray(colorLocation);

    GLuint buffId;
    glGenBuffers(1, &buffId);
    glBindBuffer(GL_ARRAY_BUFFER, buffId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(facet), &facet, GL_STATIC_DRAW);

    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE,
                          sizeof(GLVertexData), (char*)offsetof(GLVertexData, coord));
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE,
                          sizeof(GLVertexData), (char*)offsetof(GLVertexData, color));
 }

void Viewer3D::paintGL()
{
    if (provider == nullptr) return;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadMatrixf(cam->Data());

    //glEnable(GL_CULL_FACE);//don't render the 'outside' of the facets

//    const QList<ViewItem*> items = provider->Items();
//    for (ViewItem* item: items)
//    {
//        item->Paint();
//    }

}

QPointF Viewer3D::pixelPosToViewPos(const QPointF &p)
{
    return QPointF(2.0 * float(p.x()) / width() - 1.0,
                   1.0 - 2.0 * float(p.y()) / height());
}

void Viewer3D::setStates()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    setLights();

    float materialSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0f);
}

void Viewer3D::setLights()
{
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //float lightColour[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightDir[] = {0.0f, 0.0f, 1.0f, 0.0f};
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColour);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, lightColour);
    glLightfv(GL_LIGHT0, GL_POSITION, lightDir);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
    glEnable(GL_LIGHT0);
}

void Viewer3D::defaultStates()
{
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    //glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0f);
    float defaultMaterialSpecular[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, defaultMaterialSpecular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
}

void Viewer3D::mousePressEvent(QMouseEvent *event)
{
    QOpenGLWidget::mousePressEvent(event);
    if (event->isAccepted())
        return;

    if (event->buttons() & Qt::LeftButton) {
        //TODO check here maybe if selected an object
        cam->mousePressed(ViewerCam::MoveMode::SpinAroundModel, event->pos());
        event->accept();
    }
    else if (event->buttons() & Qt::RightButton) {
        cam->mousePressed(ViewerCam::MoveMode::Shift, event->pos());
        event->accept();
    }
    else if (event->buttons() & Qt::MiddleButton) {
        cam->mousePressed(ViewerCam::MoveMode::FastZoom, event->pos());
        event->accept();
    }

}

void Viewer3D::mouseReleaseEvent(QMouseEvent *event)
{
    QOpenGLWidget::mouseReleaseEvent(event);
    if (event->isAccepted())
        return;

    if (event->buttons() & Qt::LeftButton) {
        //TODO check here maybe if selected an object
        cam->mouseReleased(event->pos());
        event->accept();
    }
    else if (event->buttons() & Qt::RightButton) {
        cam->mouseReleased(event->pos());
        event->accept();
    }
    else if (event->buttons() & Qt::MiddleButton) {
        cam->mouseReleased(event->pos());
        event->accept();
    }
}

void Viewer3D::mouseMoveEvent(QMouseEvent *event)
{
    QOpenGLWidget::mouseMoveEvent(event);
    if (event->isAccepted())
        return;

    if (event->buttons() & Qt::LeftButton) {
        //TODO check here maybe if selected an object
        cam->mouseMoved(event->pos());
        event->accept();
    }
    else if (event->buttons() & Qt::RightButton) {
        cam->mouseMoved(event->pos());
        event->accept();
    }
    else if (event->buttons() & Qt::MiddleButton) {
        cam->mouseMoved(event->pos());
        event->accept();
    }
}

void Viewer3D::wheelEvent(QWheelEvent *event)
{
    QOpenGLWidget::wheelEvent(event);
    if (event->isAccepted())
        return;

    cam->wheelSpinned(event->angleDelta(), event->pos());
    event->accept();
}
