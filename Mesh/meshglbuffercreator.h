#ifndef MESHGLBUFFERCREATOR_H
#define MESHGLBUFFERCREATOR_H

#include <QObject>
#include "Utils/utils.h"
#include "meshcommon.h"
class Mesh;
class MeshGLBufferCreator : public QObject
{
    Q_OBJECT
public:
    explicit MeshGLBufferCreator(Mesh *_mesh);
    void CreateAsync();
signals:
    void Finished(bool ok);
    void Progress(QString what, double progress);

protected:
    void createAsync();
    Mesh * mesh;

    void progress(const char* what, double progress);
    double prevProgress;
};

#endif // MESHGLBUFFERCREATOR_H
