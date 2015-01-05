#ifndef VIEWERCAM_H
#define VIEWERCAM_H

#include <QMatrix4x4>
#include <QVector3D>
#include <QPoint>
#include <QObject>
class Viewer3D;

class ViewerCam : protected QObject
{
public:
    enum class ProjectionMode {
        Perspective,
        Ortho
    };

    enum class MoveMode {
        None,
        SpinAroundModel,
        SpinCamera,
        Shift,
        FastZoom
    };

    ViewerCam(Viewer3D* _viewer);
    ~ViewerCam();

    void mousePressed(MoveMode mm, const QPoint& pos);
    void mouseMoved(const QPoint& pos);
    void mouseReleased(const QPoint& pos);
    void wheelSpinned(const QPoint& angleDelta, const QPoint& pos);

    ProjectionMode GetProjectionMode() {return preojectionMode;}
    void SetProjectionMode(ProjectionMode v);

    const QMatrix4x4& Matrix() {return m;}
    const float* Data() { return m.constData();}

private:
    double r, theta, phi;
    QVector3D center, from;
    ProjectionMode preojectionMode;
    MoveMode moveMode;
    QMatrix4x4 m, shift;

    Viewer3D* viewer;
    QPoint lastPos;

    void updateMatrix();

};

#endif // VIEWERCAM_H
