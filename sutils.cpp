#include "sutils.h"

using namespace NM_SUtils;

#include <QFile>
#include <QDebug>

SUtils::SUtils()
{
}

bool SUtils::LoadPointsFromFile(Points &points, const char *filename) {
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning()<< "Open " << filename << " failed.";
        return false;
    }
    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        if (line.startsWith("v ")) {
            line.chop(1);
            QList<QByteArray> list = line.split(' ');
            point p;
            p.x = list[1].toFloat();
            p.y = list[2].toFloat();
            p.z = list[3].toFloat();
            points.append(p);
        }
    }
    f.close();
    return true;
}

bool SUtils::LoadFaceIndexFromFile(QList<int> &fa3, QList<int> &fa4, const char *filename)
{
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() <<"Open " << filename << "failed.";
        return false;
    }
    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        if (line.startsWith("f ")) {
            line.chop(1);
            QList<QByteArray> list = line.split(' ');
            if (list.size()==4) {
                for (int i=1; i<4; ++i)
                    fa3.append(list[i].toInt());
            } else {
                for (int i=1; i<5; ++i)
                    fa4.append(list[i].toInt());
            }
        }
    }
    f.close();
    return true;
}

bool SUtils::LoadFaceIndexFromFile(QList<int> &fa3, QList<int> &va3, QList<int> &fa4, QList<int> &va4, const char *filename)
{
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() <<"Open " << filename << "failed.";
        return false;
    }
    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        if (line.startsWith("f ")) {
            line.chop(1);
            QList<QByteArray> list = line.split(' ');
            if (list.size()==4) {
                for (int i=1; i<4; ++i) {
                    QList<QByteArray> val = list[i].split('/');
                    fa3.append(val[0].toInt());
                    va3.append(val[2].toInt());
                }
            } else {
                for (int i=1; i<5; ++i) {
                    QList<QByteArray> val = list[i].split('/');
                    fa4.append(val[0].toInt());
                    va4.append(val[2].toInt());
                }
            }
        }
    }
    f.close();
    return true;
}

bool SUtils::LoadNormalsFromFile(Points &points, const char *filename)
{
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning()<< "Open " << filename << " failed.";
        return false;
    }
    while (!f.atEnd()) {
        QByteArray line = f.readLine();
        if (line.startsWith("vn ")) {
            line.chop(1);
            QList<QByteArray> list = line.split(' ');
            point p;
            p.x = list[1].toFloat();
            p.y = list[2].toFloat();
            p.z = list[3].toFloat();
            points.append(p);
        }
    }
    f.close();
    return true;
}
