#ifndef VIEWWORLD_H
#define VIEWWORLD_H

#include "viewitem.h"
#include <QOpenGLVertexArrayObject>

class ViewWorld : public ViewItem
{
    Q_OBJECT
public:
    ViewWorld(QObject* parent);
    ~ViewWorld();

    // ViewItem interface
    virtual void InitGL(Viewer3D* _viewer) Q_DECL_OVERRIDE;
protected:
    virtual void doPaint() Q_DECL_OVERRIDE;
private:
    QOpenGLVertexArrayObject vao;
    GLuint vboId[1];
};

#endif // VIEWWORLD_H
