#include "viewercam.h"
#include "viewer3d.h"
#include "logger.h"
#include "common.h"
ViewerCam::ViewerCam(Viewer3D *_viewer):
    QObject(_viewer),
    viewer(_viewer)
{

    center = QVector3D(0,0,0);

    r = 100;
    theta = -PI/2;
    phi = PI/2;
    updateMatrix();
}

ViewerCam::~ViewerCam()
{

}

void ViewerCam::mousePressed(ViewerCam::MoveMode mm, const QPoint &pos)
{

    moveMode = mm;
    lastPos = pos;
}

void ViewerCam::mouseMoved(const QPoint &pos)
{

    QPoint delta = pos-lastPos;
    lastPos = pos;
    switch (moveMode) {
    case MoveMode::FastZoom: {


        break;
    }

    case MoveMode::Shift: {
//        center = QVector3D(
//                    center.x() + (delta.x()*cos(theta)*sin(phi)),
//                    center.y() + (delta.x()*sin(theta)*sin(phi)),
//                    center.z() + (delta.y()*cos(phi))
//                    );
        DBGF << center << delta;
        center.setX(center.x() + sin(theta)*delta.x());
        center.setY(center.x() + cos(theta)*delta.x());
        //center.setY(center.y() + delta.y());
        DBGF << center;
        updateMatrix();
        break;
    }

    case MoveMode::SpinAroundModel: {

        theta += delta.x()/100.0;
        phi += delta.y()/100.0;
        if (phi > PI) phi = PI;
        if (phi < 0) phi = 0;
        updateMatrix();
        break;
    }

    default:
        break;
    }

}

void ViewerCam::mouseReleased(const QPoint &pos)
{

    lastPos = pos;
    moveMode = MoveMode::None;
    updateMatrix();
}

void ViewerCam::wheelSpinned(const QPoint &angleDelta, const QPoint &pos)
{

    r -= angleDelta.y()/12.0;
    if (r < 5) r = 5;
    updateMatrix();
}

void ViewerCam::updateMatrix()
{
    from.setX(-r*cos(theta)*sin(phi));
    from.setY(r*sin(theta)*sin(phi));
    from.setZ(-r*cos(phi));
    //from += center;
    DBGF << from;
    m.setToIdentity();    
    m.lookAt(from, center, QVector3D(0,0,1));
    //m *= shift;
    if (viewer)
        viewer->update();
}

