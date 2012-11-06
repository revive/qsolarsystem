#ifndef SSPHERE3D_H
#define SSPHERE3D_H

#include <QObject>
#include <QVector3D>
#include <QColor>
#include <QGLBuffer>
#include <QGLShaderProgram>
#include "sutils.h"

class SSphere3D : public QObject
{
    Q_OBJECT
public:
    explicit SSphere3D(QObject *parent = 0);
    ~SSphere3D();
    void draw() const;

    bool loadObj(const char * filename);
    bool createBuffer();

    void dumpPoints();

signals:
    
public slots:
    
private:
    bool loadPoints(const char * filename);
    bool loadFaces(const char * filename);


    QVector3D center;
    double radius;
    QColor color;
    NM_SUtils::Points points;
    QList<int> indexFace3v;
    QList<int> indexFace4v;
    QGLBuffer mVertexBuffer;
    QGLShaderProgram mShader;
};

#endif // SSPHERE3D_H
