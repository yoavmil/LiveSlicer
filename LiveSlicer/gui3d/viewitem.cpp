#include "viewitem.h"

ViewItem::ViewItem(QObject *parent):
    QObject(parent),
    initiated(false),
    gl(nullptr)
{

}

ViewItem::~ViewItem()
{

}

void ViewItem::Paint()
{
    if (gl == nullptr)
        gl = QOpenGLContext::currentContext()->functions();
    if (!initiated)
        InitGL();
    doPaint();
}

