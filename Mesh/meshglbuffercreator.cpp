#include "meshglbuffercreator.h"
#include "mesh.h"
#include <QtConcurrent>
#include <QFuture>
#include <QColor>
MeshGLBufferCreator::MeshGLBufferCreator(Mesh *_mesh) :
    QObject(_mesh),
    mesh(_mesh)
{
    Q_ASSERT(mesh != nullptr);
}

void MeshGLBufferCreator::CreateAsync()
{
    QtConcurrent::run(this, &MeshGLBufferCreator::createAsync);
}

void MeshGLBufferCreator::createAsync()
{
    std::vector<MeshGLVertex>& glBuff = mesh->GLBuffer();
    glBuff.clear();
    glBuff.reserve(mesh->Facets().size() * 3);
    QColor qYellow = Qt::yellow, qRed = Qt::red, qGreen = Qt::green;
    glm::vec3 yellow, red, green;
    yellow.r = qYellow.redF();  yellow.g = qYellow.greenF();    yellow.b = qYellow.blueF();
    red.r = qRed.redF();  red.g = qRed.greenF();    red.b = qRed.blueF();
    green.r = qGreen.redF();  green.g = qGreen.greenF();    green.b = qGreen.blueF();

    prevProgress = 0;
    for (size_t f = 0; f < (size_t)mesh->Facets().size(); f++) {
        if (mesh->Facets()[f].flags != MeshFacet::Valid)
            continue;

        const MeshFacet& meshFacet = mesh->Facets()[f];
        glm::vec3 normal = computeNormal (
                mesh->Vertices()[meshFacet.vertexIdx[0]],
                mesh->Vertices()[meshFacet.vertexIdx[1]],
                mesh->Vertices()[meshFacet.vertexIdx[2]]);
        for (size_t v = 0; v < 3; v++) {
            glBuff.push_back(MeshGLVertex());
            MeshGLVertex& glVertex = glBuff.back();
            glVertex.normal = normal;
            glVertex.vertex = mesh->Vertices()[meshFacet.vertexIdx[v]];
            switch (v) {
            case 0:
                glVertex.rgb = yellow;
                break;
            case 1:
                glVertex.rgb = green;
                break;
            case 2:
                glVertex.rgb = red;
                break;
            }
        }
        progress("Creating GL Buffer", (double)f / mesh->Facets().size());
    }

    progress("Creating GL Buffer", 1.0);
    emit Finished(true);
}

void MeshGLBufferCreator::progress(const char *what, double progress)
{
    if (std::abs(progress - prevProgress) > 0.05 || progress == 1.0) {
        emit Progress(what, progress);
        DBGF << QString("[%1%]").arg((int)(progress * 100)) << what;
        prevProgress = progress;
    }
}

