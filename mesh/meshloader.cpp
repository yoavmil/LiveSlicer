#include "meshloader.h"
#include <QFile>
#include <QFuture>
#include <QVector3D>
#include <QtConcurrent>
#include "Utils/utils.h"

MeshLoader::MeshLoader(QObject *parent) :
    QObject(parent)
{
    numberOfFacets = 0;
    prevProgress = 0;
}

void MeshLoader::LoadAsync(const QString &_fName)
{
    fName = _fName;
    QtConcurrent::run(this, &MeshLoader::loadAsync);
}

bool MeshLoader::LoadBlocking(const QString &_fName)
{
    fName = _fName;
    {//checl if can open file
        QFile file(fName);
        file.open(QFile::ReadOnly);
        if (!file.isOpen()) {
            error = QString("couldn't open file %1: %2").arg(fName).arg(file.errorString());
            return false;
        }
    }

    fillFacets();
    markInvalidFacets();
    fillLines();

    return true;
}

void MeshLoader::loadAsync()
{
    bool ok = LoadBlocking(fName);
    emit Finished(ok);
}

void MeshLoader::readSTL(QVector<StlFacet> &stlFacets)
{
    QFile file(fName);
    file.open(QFile::ReadOnly);
    if (!file.isOpen())
        return;

    file.seek(STL_BINARY_HEADER_SIZE);

    numberOfFacets = (file.size() - STL_BINARY_HEADER_SIZE) / SIZEOF_STL_FACET;
    //TODO check here if it is binary / text STL
    stlFacets.resize(numberOfFacets);

    for (int i = 0 ; i < numberOfFacets; i++) {
        file.read((char*)&stlFacets[i], SIZEOF_STL_FACET);

        //rounding vertices
        //        for (int v = 0; v < 3; v++) {
        //            for (int c = 0; c < 3; c++) {
        //                stlFacets[i].vertices[v][c] = (int)(1000.0f * stlFacets[i].vertices[v][c]) / 1000.0f;
        //            }
        //        }

        progress("reading stl", (double)i / numberOfFacets);
    }
    file.close();
}

void MeshLoader::fillFacets()
{
    QVector<StlFacet> stlFacets;
    readSTL(stlFacets);

    int theSameCounter = 0;
    facets.reserve(numberOfFacets);
    for (int i = 0 ; i < numberOfFacets; i++) {
        StlFacet& stlFacet = stlFacets[i];
        facets.append(MeshFacet());
        MeshFacet& facet = facets.back();

        for (int v = 0; v < 3; v++) {
            if (vertexToIdx.find(stlFacet.vertices[v]) == vertexToIdx.end()) {
                int vertexIdx = vertices.length();
                vertexToIdx[stlFacet.vertices[v]] = vertexIdx;
                vertices.append(stlFacet.vertices[v]);
            }
            else {
                theSameCounter++;
            }
            facet.vertexIdx[v] = vertexToIdx[stlFacet.vertices[v]];
        }

        progress("finding vertices", (double)i / numberOfFacets);
    }
    progress("finding vertices", 1.0);
}

void MeshLoader::markInvalidFacets()
{
    //mark invalid vacets
    int invalidCounter = 0;
    for (int i = 0 ; i < numberOfFacets; i++) {
        MeshFacet& facet = facets[i];
        glm::vec3& v0 = vertices[facet.vertexIdx[0]];
        glm::vec3& v1 = vertices[facet.vertexIdx[1]];
        glm::vec3& v2 = vertices[facet.vertexIdx[2]];
        if (v0 == v1 || v0 == v2 || v1 == v2) {
            facet.flags = MeshFacet::NoArea;
            invalidCounter++;
            DBGF << i << "found invalid facet with 2 or more same vertices" << v0 << v1 << v2;
        }

        progress("checking factets", (double)i / numberOfFacets);
    }
    progress("checking factets", 1.0);
}

void MeshLoader::fillLines()
{
    for (int i = 0 ; i < numberOfFacets; i++) {
        MeshFacet& facet = facets[i];
        if (facet.flags != MeshFacet::Valid)
            continue;
        for (int v = 0; v < 3; v++) {
            LineDirLess line;
            line.v0 = vertices[facet.vertexIdx[v]];
            line.v1 = vertices[facet.vertexIdx[(v+1) % 3]];

            QList<int>& lineFacetIdxs = lineToFacetsIdx[line];

            if (!lineFacetIdxs.contains(i)) {
                lineFacetIdxs.append(i);
            }

            foreach (int facetIdx, lineFacetIdxs) {
                MeshFacet& somefacet = facets[facetIdx];
                foreach (int otherFacetIdx, lineFacetIdxs) {
                    if (facetIdx == otherFacetIdx)
                        continue;
                    MeshFacet& otherFacet = facets[otherFacetIdx];
                    if (!somefacet.neighborsIdx.contains(otherFacetIdx))
                        somefacet.neighborsIdx.append(otherFacetIdx);
                    if (!otherFacet.neighborsIdx.contains(facetIdx))
                        otherFacet.neighborsIdx.append(facetIdx);
                }
            }
        }

        progress("finding neighbor facets", (double)i / numberOfFacets);
    }

    //counting neighbor count
    QMap<int, int> neighborCounter;
    for (int i = 0 ; i < numberOfFacets; i++) {
        MeshFacet& facet = facets[i];
        neighborCounter[facet.neighborsIdx.length()]++;
        if (facet.neighborsIdx.size() != 3) {
            facet.flags = MeshFacet::NoNeighbors;
        }
    }
    QMapIterator<int, int> i(neighborCounter);
    while (i.hasNext()) {
        i.next();
        DBGF << i.key() << ": " << i.value();
    }
    progress("finding neighbor facets", 1);
}

void MeshLoader::progress(const char *what, double progress)
{
    if (std::abs(progress - prevProgress) > 0.05 || progress == 1.0) {
        emit Progress(what, progress);
        DBGF << QString("[%1%]").arg((int)(progress * 100)) << what;
        prevProgress = progress;
    }
}
