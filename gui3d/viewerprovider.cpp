#include <QMutexLocker>

#include "viewerprovider.h"
#include "viewitem.h"
#include "logger.h"

ViewerProvider::ViewerProvider(QObject *parent) : QObject(parent)
{

}

ViewerProvider::~ViewerProvider()
{

}

void ViewerProvider::InitGL(Viewer3D* _viewer)
{
    viewer = _viewer;
    for(ViewItem *vi : items)
        vi->InitGL(viewer);
}

void ViewerProvider::AddItem(ViewItem *item)
{
    QMutexLocker ml(&itemsMutex);
    newItems.append(item);    
}

void ViewerProvider::RemoveItem(ViewItem *item)
{
    QMutexLocker ml(&itemsMutex);
    oldItems.append(item);
}

const QList<ViewItem*> &ViewerProvider::Items()
{
    QMutexLocker ml(&itemsMutex);
    if (newItems.length() > 0) {
        items.append(newItems);
        newItems.clear();
    }

    if (oldItems.length() > 0) {
        for(auto oldItem : oldItems) {
            items.removeAll(oldItem);
        }
        oldItems.clear();
    }

    return items;
}

