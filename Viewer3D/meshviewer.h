#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QMutex>
#include <QGLShaderProgram>
#include <glm/vec2.hpp>
class Mesh;
class GLWrap;
class Camera;
class QOpenGLDebugLogger;
class MeshViewer : public QOpenGLWidget
{
public:
    MeshViewer(QWidget* parent);
    ~MeshViewer();

    void SetMesh(Mesh* mesh);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void wheelEvent(QWheelEvent *);

    void meshLoaded(bool ok);

protected:
    GLWrap* gl;

    // QOpenGLWidget interface
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void initShaders();

    Camera* cam;
    glm::vec2 prevMousePos;

    void paintMesh();
    Mesh* mesh;

    QGLShaderProgram program;

    glm::vec3 lightPos();

private:
    QMutex viewablesMutex;

protected slots:
    void timerTimeout();
};

#endif // GLWIDGET_H
