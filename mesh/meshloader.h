#ifndef MODEL_H
#define MODEL_H

#include <unordered_map>
#include <QObject>
#include <QString>
#include "Utils/utils.h"
#include "meshcommon.h"

class MeshLoader : public QObject
{
    Q_OBJECT
public:
    explicit MeshLoader(QObject *parent = 0);
    void LoadAsync(const QString& _fName);
    bool LoadBlocking(const QString& fName);
    QString fName;
    QString error;

    QList<MeshFacet> facets;
    std::unordered_map<LineDirLess, QList<int>> lineToFacetsIdx;
    QList<glm::vec3> vertices;
    std::unordered_map<glm::vec3, int> vertexToIdx;

signals:
    void Finished(bool ok);
    void Progress(QString what, double progress);

private:
    void loadAsync();
    void readSTL(QVector<StlFacet>& stlFacets);
    void fillFacets();
    void markInvalidFacets();
    void fillLines();

    void progress(const char* what, double progress);
    double prevProgress;
    int numberOfFacets;
};

#endif // MODEL_H
