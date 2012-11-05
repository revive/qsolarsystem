#include "ssphere3d.h"
#include <QDebug>

SSphere3D::SSphere3D(QObject *parent) :
    QObject(parent)
{
}

SSphere3D::~SSphere3D()
{

}

void SSphere3D::draw() const
{

}

bool SSphere3D::loadPoints(const char *filename)
{
    using namespace NM_SUtils;
    return SUtils::LoadPointsFromFile(points, filename);
}

void SSphere3D::dumpPoints()
{
    for (int i = 0; i<points.size(); ++i) {
        qWarning()<<points.at(i).x << " " << points.at(i).y << " " << points.at(i).z;
    }
}

