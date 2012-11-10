#ifndef SSPHERE3D_H
#define SSPHERE3D_H

#include <QObject>
#include <QVector3D>
#include <QColor>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include <QGLWidget>
#include <QMatrix4x4>
#include "sutils.h"

class SSphere3D : public QObject
{
    Q_OBJECT
public:
    explicit SSphere3D(QObject *parent = 0);
    ~SSphere3D();
    void draw();

    bool loadObj();
    bool loadShader();
    bool createBuffer();

    void dumpPoints();
    void setProjectionAndViewMatrix(const QMatrix4x4 &pm, const QMatrix4x4 &vm);
    void setTexture(QGLWidget * widget);
    void loadTexture();
    void setAxialTilt(double angle);
    void rotate(double angle);

signals:
    
public slots:
    
private:
    bool loadPoints(const char * filename);
    bool loadFaces(const char * filename);
    bool loadNormals(const char * filename);


    QVector3D center;
    double radius;
    QColor color;
    NM_SUtils::Points points;
    NM_SUtils::Points normals;
    QList<int> indexFace3v;
    QList<int> indexFace3n;
    QList<int> indexFace4v;
    QList<int> indexFace4n;
    QGLBuffer mVertexBuffer;
    QGLBuffer mNormalBuffer;
    QGLShaderProgram mShader;
    QGLBuffer mIndexBuffer;
    QMatrix4x4 mProjectionMatrix;
    QMatrix4x4 mViewMatrix;
    QMatrix4x4 mModelMatrix;
    double m_axialTilt;
    GLuint m_texture;
};

#endif // SSPHERE3D_H
