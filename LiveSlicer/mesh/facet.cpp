#include "facet.h"

#include <QVector3D>

Facet::Facet()
{
    for(int i = 0; i < 3; i++) { v[i] = nullptr; }
    n = nullptr;
    mesh = nullptr;
}

Facet::~Facet()
{

}

