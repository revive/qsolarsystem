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
        if (line.startsWith('v')) {
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
