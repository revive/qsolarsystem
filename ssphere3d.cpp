#include "ssphere3d.h"
#include <QDebug>
#include <QImage>
#include <GL/glext.h>

SSphere3D::SSphere3D(QObject *parent) :
    QObject(parent),
    mVertexBuffer(QGLBuffer::VertexBuffer),
    mPvmMatrix()
{
}

SSphere3D::~SSphere3D()
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
    return SUtils::LoadFaceIndexFromFile(indexFace3v, indexFace3n, indexFace4v, indexFace4n, filename);
}

bool SSphere3D::loadNormals(const char *filename)
{
    using namespace NM_SUtils;
    return SUtils::LoadNormalsFromFile(normals, filename);
}

bool SSphere3D::loadObj()
{
    QString filename(":/model/sphere.obj");
    bool result;
    result = loadPoints(filename.toStdString().c_str());
    if (result)
        result = loadFaces(filename.toStdString().c_str());
    if (result)
        result = loadNormals(filename.toStdString().c_str());
    return result;
}

bool SSphere3D::loadShader()
{
    bool result;
    result = mShader.addShaderFromSourceFile(QGLShader::Vertex, ":/model/sphere.vert");
    if (!result) {
        qWarning() << mShader.log();
    }
    result = mShader.addShaderFromSourceFile(QGLShader::Fragment, ":/model/sphere.frag");
    if (!result) {
        qWarning() << mShader.log();
    }
    result = mShader.link();
    if ( !result )
        qWarning() << "Could not link shader program:" << mShader.log();

    return result;
}

bool SSphere3D::createBuffer()
{
    using namespace NM_SUtils;
    QList<float> vertexlist;
    QList<float> normallist;

    for (int i=0; i<indexFace3v.size(); ++i) {
        int index = indexFace3v.at(i) - 1;
        vertexlist.append(points.at(index).x);
        vertexlist.append(points.at(index).y);
        vertexlist.append(points.at(index).z);
        index = indexFace3n.at(i) - 1;
        normallist.append(normals.at(index).x);
        normallist.append(normals.at(index).y);
        normallist.append(normals.at(index).z);
    }
    for (int i=0; i<indexFace4v.size(); ++i) {
        int index = indexFace4v.at(i) - 1;
        vertexlist.append(points.at(index).x);
        vertexlist.append(points.at(index).y);
        vertexlist.append(points.at(index).z);
        index = indexFace4n.at(i) - 1;
        normallist.append(normals.at(index).x);
        normallist.append(normals.at(index).y);
        normallist.append(normals.at(index).z);
    }
    mVertexBuffer.create();
    mVertexBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mVertexBuffer.bind();
    float *fvertex = new float[vertexlist.size()];
    for (int i=0; i<vertexlist.size(); ++i) {
        fvertex[i] = vertexlist.at(i);
    }
    mVertexBuffer.allocate(fvertex, vertexlist.size() * sizeof(float));
    delete[] fvertex;
    fvertex = 0;
    mNormalBuffer.create();
    mNormalBuffer.setUsagePattern(QGLBuffer::StaticDraw);
    mNormalBuffer.bind();
    fvertex = new float[normallist.size()];
    for (int i=0; i<normallist.size(); ++i) {
        fvertex[i] = normallist.at(i);
    }
    mNormalBuffer.allocate(fvertex, normallist.size()* sizeof(float));
    delete[] fvertex;
    return true;
}

void SSphere3D::dumpPoints()
{
    for (int i = 0; i<points.size(); ++i) {
        qWarning()<<points.at(i).x << " " << points.at(i).y << " " << points.at(i).z;
    }
}

void SSphere3D::setProjectionAndViewMatrix(const QMatrix4x4 &pm, const QMatrix4x4 &vm)
{
    mPvmMatrix = mPvmMatrix * pm * vm;
}

void SSphere3D::setTexture(QGLWidget * widget)
{
    m_texture = widget->bindTexture(":/pic/t1.png");
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void SSphere3D::loadTexture()
{
    QImage image(":/pic/wm.png");
    image = image.convertToFormat(QImage::Format_ARGB32);
    glGenTextures(1, &m_texture);
    qWarning()<<m_texture;
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, image.width(), image.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, image.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void SSphere3D::draw()
{
    if (!mShader.bind()) {
        qWarning()<<"Bind shader failed.";
        return;
    }
    mVertexBuffer.bind();
    mShader.setAttributeBuffer("vertex", GL_FLOAT, 0, 3);
    mShader.enableAttributeArray("vertex");
    mNormalBuffer.bind();
    mShader.setAttributeBuffer("normal", GL_FLOAT, 0, 3);
    mShader.enableAttributeArray("normal");
    mShader.setUniformValue("pvmMatrix", mPvmMatrix);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    mShader.setUniformValue("texture", 0);
    int nFace3 = indexFace3v.size()/3;
    glDrawArrays( GL_TRIANGLES, 0, nFace3*3 );
    int nFace4 = indexFace4v.size()/4;
    glDrawArrays( GL_QUADS, nFace3*3, nFace4 * 4);
}
