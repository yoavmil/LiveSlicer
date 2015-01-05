#ifndef VIEWITEM_H
#define VIEWITEM_H

#include <QGL>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QObject>
#include <QVector3D>

class ViewItem : public QObject
{
    Q_OBJECT

public:
    explicit ViewItem(QObject *parent = 0);
    ~ViewItem();
//    bool OneColor() {return true;}
//    QColor GetColor() {return color;}

    void Paint();
    virtual void InitGL() {initiated = true;}
    bool initiated;

signals:

public slots:

protected:
    QVector3D Translate, Rotate, Scale;
    QOpenGLFunctions* gl;

    virtual void doPaint() = 0;
};

#endif // VIEWITEM_H
