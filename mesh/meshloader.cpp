#include <QFileInfo>
#include <QVector>

#include "meshloader.h"
#include "logger.h"
#include "exceptions.h"
#include "mesh.h"
#include "viewerprovider.h"
#include "viewsimplemesh.h"

MeshLoader::MeshLoader(MeshLoaderParams _mlp):
    Task(true),
    mlp(_mlp)
{
    DBGF;
    if (mlp.mesh == nullptr) {
        mlp.mesh = new Mesh();
    }
}

MeshLoader::~MeshLoader()
{

}

const QString &MeshLoader::ShortFileName()
{
    //TODO fix this
    return FileName();
}

void MeshLoader::doStart()
{
    try {
    DBGF << FileName();
    openFile();
    findFileType();
    readFile();
    saveModel();
    }
    catch(Exception ex) {
        DBGF << (int)ex.type << ex.msg;
    }
}

void MeshLoader::doResume()
{

}

void MeshLoader::openFile()
{
    file.setFileName(mlp.fName);
    if (!file.open(QFile::ReadOnly)) {
        throw Exception(Exception::Type::File,
                        QString("failed to open %1: %2")
                        .arg(mlp.fName)
                        .arg(file.errorString()));
    }
}

void MeshLoader::findFileType()
{
    QFileInfo fi(file);
    QString suffix = fi.suffix().toLower();
    if (suffix == "stl") {
        //TODO assume for now it is binary stl
        meshType = MeshType::StlBinary;
    }
    else {
        throw Exception(Exception::Type::NotSupported, QString("format %1 not supported").arg(suffix));
    }
}

void MeshLoader::readFile()
{
    switch (meshType) {
    case MeshType::StlBinary:
        readBinStl();
        break;
    default:
        throw Exception(Exception::Type::NotSupported, QString("format not supported"));
        break;
    }
}

int MeshLoader::GetProgress()
{
    return 0;//TODO me
}

QString MeshLoader::GetTitle()
{
    return "";//TODO me
}

QString MeshLoader::GetTooltip()
{
    return "";//TODO me
}

void MeshLoader::readBinStl()
{
    int fileSize = file.size();
    const int numberOfFacets = (fileSize - STL_BINARY_HEADER_SIZE) / SIZEOF_STL_FACET;

    file.seek(STL_BINARY_HEADER_SIZE);
    setTitle(QString("%1: Reading file").arg(ShortFileName()));
    setProgress(0);

    stlFacets.resize(numberOfFacets);

    for (int i = 0 ; i < numberOfFacets; i++) {
        file.read((char*)&stlFacets[i], SIZEOF_STL_FACET);
        setProgress(i*100.0/numberOfFacets);
    }
}

void MeshLoader::saveModel()
{
    ViewItem* vi = nullptr;
    ViewSimpleMesh* vsm;
    switch (meshType) {
    case MeshType::StlBinary:
        vi = vsm = new ViewSimpleMesh();
        vsm->SetFacets(stlFacets);
        break;
    default:
        break;
    }

    if (vi != nullptr)
        mlp.viewProvider->AddItem(vi);
}

