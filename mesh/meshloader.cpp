#include <QFileInfo>
#include <functional>   // std::less
#include <map>

#include "meshloader.h"
#include "logger.h"
#include "exceptions.h"
#include "mesh.h"
#include "viewerprovider.h"
#include "viewsimplemesh.h"
#include "viewmesh.h"

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
    if (shortFileName.isEmpty()) {
        QFileInfo fi(file);
        shortFileName = fi.completeBaseName();
    }
    return shortFileName;
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
    ViewMesh* viewMesh = nullptr;
    switch (meshType) {
    case MeshType::StlBinary:
        vi = vsm = new ViewSimpleMesh();
        vsm->SetFacets(stlFacets);

        DBGF;

        createMeshVectors();
        viewMesh = new ViewMesh(mlp.mesh);

        break;
    default:
        break;
    }

    if (vi != nullptr)
        mlp.viewProvider->AddItem(vi);

    if (viewMesh != nullptr)
        mlp.viewProvider->AddItem(viewMesh);
}

QDebug operator<< (QDebug d, const glm::vec3 & v) {
    d << QString("[%1, %2, %3]").arg(v[0]).arg(v[1]).arg(v[2]);
    return d;
}

namespace std{
template<>
bool std::less<glm::vec3>::operator () (const glm::vec3& a, const glm::vec3& b) const
{
    for (int i = 0; i < 3; i++) {
        if (a[i] < b[i])
            return true;
        if (a[i] > b[i])
            return false;
    }
    return false;
}
}

void MeshLoader::createMeshVectors()
{
    std::vector<GLFacetData>& facets = mlp.mesh->facets;
    const glm::vec3 defaultColor = glm::vec3(0.5, 0.5, 0.5);
    setTitle(QString("%1: creating vertices arrays").arg(ShortFileName()));
    facets.resize(stlFacets.size());
    for (int i = 0; i < stlFacets.length(); i++) {
        const StlFacet& stlFacet = stlFacets[i];
        setProgress(i*95.0/stlFacets.length());
        GLFacetData& facet = facets[i];

        glm::vec3 normal = glm::vec3(stlFacets[i].normal[0], stlFacets[i].normal[1], stlFacets[i].normal[2]);

        for (int v = 0; v < 3; v++) {             
            facet.vertices[v].coord = stlFacet.vertices[v];
            facet.vertices[v].normal = normal;
            facet.vertices[v].color = defaultColor;
        }   
    }

    setProgress(100);
}

