#include "ssphere3d.h"

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

void SSphere3D::setCenter(QVector3D &p)
{
    center = p;
}

void SSphere3D::setRadius(double r)
{
    radius = r;
}

void SSphere3D::setColor(QColor c)
{
    color = c;
}
