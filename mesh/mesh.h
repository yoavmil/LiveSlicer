#ifndef MESH_H
#define MESH_H

#include <QObject>
#include <unordered_map>
#include <QOpenGLFunctions>
#include "Utils/bbox.h"
#include "meshcommon.h"
#include "Utils/utils.h"

class MeshLoader;
class MeshGLBufferCreator;

class Mesh : public QObject
{
    Q_OBJECT
public:
    explicit Mesh(QObject *parent = 0);
    void Load(QString _fName);

    std::vector<MeshGLVertex>& GLBuffer();
    QList<MeshFacet>& Facets() { return facets; }
    QList<glm::vec3>& Vertices() { return vertices; }

    glm::vec3 Center() {return center;}
    GLuint& GlVertexBuffId() { return glVertexBuffId; }

    BBox GetBbox() const;

signals:
    void LoadingFinished(bool ok);
    void Progress(QString what, double progress);

protected slots:
    void loadingFinished(bool ok);
    void progress(QString what, double progress);
    void glBufferCreatefinished(bool ok);

protected:
    QString fName;

    //mesh
    QList<MeshFacet> facets;
    std::unordered_map<LineDirLess, QList<int>> lineToFacetsIdx;
    QList<glm::vec3> vertices;
    std::unordered_map<glm::vec3, int> vertexToIdx;

    BBox bbox;
    glm::vec3 center;

    //gl data
    std::vector<MeshGLVertex> vertexBuff;
    std::vector<GLuint> elementBuff;
    GLuint glVertexBuffId;
    GLuint glElemntBuffId;

    MeshLoader* loader;
    MeshGLBufferCreator* glBufferCreator;
};

#endif // MESH_H
