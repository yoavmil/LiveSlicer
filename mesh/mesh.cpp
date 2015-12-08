#include "mesh.h"
#include "meshloader.h"
#include "meshglbuffercreator.h"
Mesh::Mesh(QObject *parent) : QObject(parent)
{
    loader = nullptr;
    glBufferCreator = nullptr;
    glVertexBuffId = 0;
}

void Mesh::Load(QString _fName)
{
    fName = _fName;

    Q_ASSERT(loader == nullptr);
    Q_ASSERT(glBufferCreator == nullptr);
    loader = new MeshLoader(this);
    connect(loader, SIGNAL(Finished(bool)),
            this, SLOT(loadingFinished(bool)), Qt::QueuedConnection);
    connect(loader, SIGNAL(Progress(QString,double)),
            this, SLOT(progress(QString,double)), Qt::QueuedConnection);
    loader->LoadAsync(fName);

}

std::vector<MeshGLVertex> &Mesh::GLBuffer()
{
    return vertexBuff;
}

void Mesh::loadingFinished(bool ok)
{
    if (ok) {
        facets = std::move(loader->facets);
        lineToFacetsIdx = std::move(loader->lineToFacetsIdx);
        vertices = std::move(loader->vertices);
        vertexToIdx = std::move(loader->vertexToIdx);
    }
    loader->deleteLater();
    loader = nullptr;

    DBGF << vertices.size();
    for (size_t v = 0; v < vertices.size(); v++) {
        center += vertices[v];
        bbox.Include(vertices[v]);
    }
    center /= vertices.size();
    DBGF << center;
    DBGF << bbox.Min() << bbox.Max();

    glBufferCreator = new MeshGLBufferCreator(this);
    connect(glBufferCreator, SIGNAL(Finished(bool)),
            this, SLOT(glBufferCreatefinished(bool)), Qt::QueuedConnection);
    connect(glBufferCreator, SIGNAL(Progress(QString,double)),
            this, SLOT(progress(QString,double)));
    glBufferCreator->CreateAsync();
}

void Mesh::progress(QString what, double progress)
{
    emit Progress(what, progress);
}

void Mesh::glBufferCreatefinished(bool ok)
{
    glBufferCreator->deleteLater();
    glBufferCreator = nullptr;
    emit LoadingFinished(ok);
}

BBox Mesh::GetBbox() const
{
    return bbox;
}
