#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "openglprogram.h"
class ViewerProvider;
class ViewerCam;

class Viewer3D : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    Viewer3D(QWidget* parent);
    ~Viewer3D();
    void SetProvider(ViewerProvider* vp);
    ViewerCam* Cam();

    // QOpenGLWidget interface
protected:
    virtual void initializeGL() Q_DECL_OVERRIDE;
    virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    virtual void paintGL() Q_DECL_OVERRIDE;

private:
    ViewerProvider* provider;
    QPointF pixelPosToViewPos(const QPointF& p);
    float viewNeer, viewFar;
    QColor backGround;
    ViewerCam* cam;

    int vertexLocation;
    int normalLocation;
    int colorLocation;
    int MVMatLocation;
    int PMatLocation;

    void setStates();
    void defaultStates();
    void setLights();
    void setProjectionMat();
    void initShaders();

protected:
    // QWidget interface
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event )Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
};


#endif // VIEWER3D_H
