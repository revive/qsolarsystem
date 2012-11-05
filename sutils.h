#ifndef SUTILS_H
#define SUTILS_H

#include <QVector>
namespace NM_SUtils {

typedef struct {
    float x;
    float y;
    float z;
} point;

typedef QVector<point> Points;

}

class SUtils
{
public:
    SUtils();

    static bool LoadPointsFromFile(NM_SUtils::Points & points, const char * filename);

};


#endif // SUTILS_H