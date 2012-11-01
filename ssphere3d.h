#ifndef SSPHERE3D_H
#define SSPHERE3D_H

#include <QObject>
#include <QVector3D>
#include <QColor>

class SSphere3D : public QObject
{
    Q_OBJECT
public:
    explicit SSphere3D(QObject *parent = 0);
    ~SSphere3D();
    void setColor(QColor c);
    void setCenter(QVector3D & p);
    void setRadius(double r);
    void draw() const;

signals:
    
public slots:
    
private:
    QVector3D center;
    double radius;
    QColor color;
};

#endif // SSPHERE3D_H
