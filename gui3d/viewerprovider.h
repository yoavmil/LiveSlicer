#ifndef VIEWPROVIDER_H
#define VIEWPROVIDER_H

#include <QObject>
#include <QMutex>

class ViewItem;
class Viewer3D;

class ViewerProvider : public QObject
{
    Q_OBJECT
public:
    explicit ViewerProvider(QObject *parent = 0);
    ~ViewerProvider();

    void InitGL(Viewer3D *viewer);

    void AddItem(ViewItem* item);
    void RemoveItem(ViewItem* item);
    const QList<ViewItem*>& Items();
signals:

public slots:

private:
    QList<ViewItem*> items;
    QList<ViewItem*> newItems, oldItems;
    QMutex itemsMutex;
    Viewer3D* viewer;
};

#endif // VIEWPROVIDER_H
