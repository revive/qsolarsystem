#include "ssphere3d.h"
#include <QDebug>

SSphere3D::SSphere3D(QObject *parent) :
    QObject(parent),
    mVertexBuffer(QGLBuffer::VertexBuffer)
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

bool SSphere3D::loadFaces(const char *filename)
{
    using namespace NM_SUtils;
    return SUtils::LoadFaceIndexFromFile(indexFace3v, indexFace4v, filename);
}

bool SSphere3D::loadObj(const char *filename)
{
    bool result;
    result = loadPoints(filename);
    if (result)
        result = loadFaces(filename);
    return result;
}

bool SSphere3D::createBuffer()
{
    using namespace NM_SUtils;
    mVertexBuffer.create();
    QList<float> vertexlist;

    for (int i=0; i<indexFace3v.size(); ++i) {
        int index = indexFace3v.at(i) - 1;
        vertexlist.append(points.at(index).x);
        vertexlist.append(points.at(index).y);
        vertexlist.append(points.at(index).z);
    }
    for (int i=0; i<indexFace4v.size(); ++i) {
        int index = indexFace4v.at(i) - 1;
        vertexlist.append(points.at(index).x);
        vertexlist.append(points.at(index).y);
        vertexlist.append(points.at(index).z);
    }
    mVertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mVertexBuffer.bind();
    float *fvertex = new float[vertexlist.size()];
    for (int i=0; i<vertexlist.size(); ++i) {
        fvertex[i] = vertexlist.at(i);
    }
    mVertexBuffer.allocate(fvertex, vertexlist.size() * sizeof(float));
    delete[] fvertex;
    return true;
}

void SSphere3D::dumpPoints()
{
    for (int i = 0; i<points.size(); ++i) {
        qWarning()<<points.at(i).x << " " << points.at(i).y << " " << points.at(i).z;
    }
}

