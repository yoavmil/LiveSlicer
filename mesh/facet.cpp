#include "facet.h"

#include <QVector3D>

Facet::Facet()
{
    for(int i = 0; i < 3; i++) { v[i] = -1; }
    n = -1;
    mesh = nullptr;
}

Facet::~Facet()
{

}

