#ifndef SSPHERE3D_H
#define SSPHERE3D_H

#include <QObject>
#include <QVector3D>
#include <QColor>
#include "sutils.h"

class SSphere3D : public QObject
{
    Q_OBJECT
public:
    explicit SSphere3D(QObject *parent = 0);
    ~SSphere3D();
    void draw() const;
    bool loadPoints(const char * filename);
    void dumpPoints();

signals:
    
public slots:
    
private:
    QVector3D center;
    double radius;
    QColor color;
    NM_SUtils::Points points;
};

#endif // SSPHERE3D_H
