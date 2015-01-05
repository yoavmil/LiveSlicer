#ifndef VIEWPROVIDER_H
#define VIEWPROVIDER_H

#include <QObject>
#include <QMutex>

class ViewItem;

class ViewerProvider : public QObject
{
    Q_OBJECT
public:
    explicit ViewerProvider(QObject *parent = 0);
    ~ViewerProvider();

    void InitGL();

    void AddItem(ViewItem* item);
    void RemoveItem(ViewItem* item);
    const QList<ViewItem*>& Items();
signals:

public slots:

private:
    QList<ViewItem*> items;
    QList<ViewItem*> newItems, oldItems;
    QMutex itemsMutex;
};

#endif // VIEWPROVIDER_H
