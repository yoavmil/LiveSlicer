#ifndef VIEWER3D_H
#define VIEWER3D_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class ViewerProvider;
class TrackBall;

class Viewer3D : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    Viewer3D(QWidget* parent);
    ~Viewer3D();
    void SetProvider(ViewerProvider* vp);

protected:


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
    TrackBall* trackBall;
    void setStates();
    void defaultStates();
    void setLights();
    void setProjectionMat();

protected:
    // QWidget interface
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent *event )Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
};


#endif // VIEWER3D_H
