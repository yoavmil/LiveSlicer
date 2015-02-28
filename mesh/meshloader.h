#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <QFile>
#include <QVector>

#include "task.h"
#include "common.h"

class Mesh;
class ViewerProvider;


struct MeshLoaderParams
{
    MeshLoaderParams(const QString& _fName):
        ignoreNormals(true),
        mesh(nullptr),
        fName(_fName),
        viewProvider(nullptr)
    {}

    bool ignoreNormals;
    Mesh* mesh;
    QString fName;
    ViewerProvider* viewProvider;
};

class MeshLoader : public Task
{
    Q_OBJECT

public:
    enum class MeshType
    {
        StlBinary,
        StlAscii,
        Obj
    };
    MeshLoader(MeshLoaderParams _mlp);
    ~MeshLoader();
    const QString& FileName() {return mlp.fName;}
    const QString& ShortFileName();

    // Task interface
    virtual QString GetTitle();
    virtual QString GetTooltip();

    MeshType meshType;

protected:
    virtual void doStart();
    virtual void doResume();

private:
    QFile file;
    QString shortFileName;
    MeshLoaderParams mlp;
    QVector<StlFacet> stlFacets;

    void openFile();
    void findFileType();
    void readFile();
    void readBinStl();
    void saveModel();
    void createMeshVectors();
};

#endif // MESHLOADER_H
