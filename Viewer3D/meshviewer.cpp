#include <QMouseEvent>
#include <QTimer>
#include "mesh.h"
#include "meshviewer.h"
#include "Utils/utils.h"
#include "glwrap.h"
#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"

MeshViewer::MeshViewer(QWidget *parent):
    QOpenGLWidget(parent),
    mesh(nullptr)
{
    gl = new GLWrap();
    cam = new Camera(this);
    connect(cam, SIGNAL(CamChanged()), this, SLOT(repaint()));
}

void MeshViewer::initializeGL()
{
    gl->Init();
    gl->ClearColor(QColor(Qt::blue).darker());
    gl->Enable(GLCap::DepthTest, true);
    gl->Enable(GLCap::CullFaces, true);
    initShaders();
}

MeshViewer::~MeshViewer()
{
    delete gl;
}

void MeshViewer::SetMesh(Mesh *mesh)
{
    this->mesh = mesh;
    connect(mesh, &Mesh::LoadingFinished, this, &MeshViewer::meshLoaded);
}

void MeshViewer::mousePressEvent(QMouseEvent *e)
{
    prevMousePos = glm::vec2(e->x(), e->y());
    if (e->modifiers() == Qt::ShiftModifier && (e->button() == Qt::LeftButton || e->button() == Qt::RightButton)) {
        cam->SetMotionMode(Camera::Shift);
    }
    else if (e->button() == Qt::LeftButton) {
        cam->SetMotionMode(Camera::AroundEye);
    }
    else if (e->button() == Qt::MiddleButton) {
        cam->SetMotionMode(Camera::Forward);
    }
    else {
        cam->SetMotionMode(Camera::AroundCenter);
    }
}

void MeshViewer::mouseReleaseEvent(QMouseEvent *)
{
}

void MeshViewer::mouseMoveEvent(QMouseEvent *e)
{
    glm::vec2 currMousePos(e->x(), e->y());
    cam->MouseMove(currMousePos - prevMousePos);
    prevMousePos = currMousePos;
}

void MeshViewer::wheelEvent(QWheelEvent *e)
{
    cam->Zoom(e->delta());
}

void MeshViewer::meshLoaded(bool ok)
{
    if (ok) {
        repaint();
    }
}

void MeshViewer::resizeGL(int w, int h)
{
    gl->Viewport(0, 0, w, h);
}

void MeshViewer::paintGL()
{
    gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    paintMesh();
}

void MeshViewer::initShaders()
{
    QGLShader vertexShader(QGLShader::Vertex);
    vertexShader.compileSourceFile(":/shaders/shaders/simplevertshader.vert");

    QGLShader fragShader(QGLShader::Fragment);
    fragShader.compileSourceFile(":/shaders/shaders/simplefragshader.frag");

    bool ok = true;
    ok = ok && program.addShader(&vertexShader);
    ok = ok && program.addShader(&fragShader);
    ok = ok && program.link();
    ok = ok && program.bind();
    if (!ok) {
        WRNF << "failed to load program";
        WRNF << program.log();
        return;
    }
}


void MeshViewer::paintMesh()
{
    if (mesh == nullptr)
        return;

    if (mesh->GLBuffer().size() == 0)
        return;

    if (mesh->GlVertexBuffId() == 0) {
        //need to load the data
        mesh->GlVertexBuffId() = gl->GenBuffer();
        gl->BindArrayBuffer(mesh->GlVertexBuffId());
        gl->ArrayBufferData(mesh->GLBuffer().size() * sizeof(MeshGLVertex), mesh->GLBuffer().data());
        glm::vec3 farFromBBox = mesh->GetBbox().Max() + (mesh->GetBbox().Max() - mesh->Center()) * 0.5f;
        DBGF << farFromBBox << mesh->GetBbox().Max() << mesh->Center();

        cam->SetPerspective(width(), height(), 0.01, glm::length(mesh->GetBbox().Max() - mesh->GetBbox().Min()) * 2);
        cam->LookAt(farFromBBox, mesh->Center());
    }

    program.bind();

    //uniforms
    int mvpLocation = program.uniformLocation("mvpMat");
    int mvLocation = program.uniformLocation("mvMat");
    int normalMatLocation = program.uniformLocation("normalMat");
    int lightPosLocation = program.uniformLocation("lightPos");

    //attributes
    int vertexLocation = program.attributeLocation("vertex");
    int rgbLocation = program.attributeLocation("rgb");
    int normalLocation = program.attributeLocation("normal");

    gl->UniformMatrix(mvpLocation, cam->MVPMat());
    gl->UniformMatrix(mvLocation, cam->MVMat());
    gl->UniformMatrix(normalMatLocation, cam->NormalMatrix());
    gl->Uniform(lightPosLocation, lightPos());

    gl->BindArrayBuffer(mesh->GlVertexBuffId());

    gl->EnableVertexAttribArray(vertexLocation, true);
    gl->EnableVertexAttribArray(rgbLocation, true);
    gl->EnableVertexAttribArray(normalLocation, true);

    gl->VertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(MeshGLVertex), offsetof(MeshGLVertex, vertex));
    gl->VertexAttribPointer(rgbLocation,    3, GL_FLOAT, GL_FALSE, sizeof(MeshGLVertex), offsetof(MeshGLVertex, rgb));
    gl->VertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(MeshGLVertex), offsetof(MeshGLVertex, normal));

    gl->DrawArrays(GL_TRIANGLES, 0, mesh->GLBuffer().size());

    gl->EnableVertexAttribArray(vertexLocation, false);
    gl->EnableVertexAttribArray(rgbLocation,    false);
    gl->EnableVertexAttribArray(normalLocation, false);

    gl->BindArrayBuffer(0);
}

glm::vec3 MeshViewer::lightPos()
{
    return cam->Eye();
}
