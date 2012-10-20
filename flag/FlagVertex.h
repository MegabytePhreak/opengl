#ifndef _FLAGVERTEX_H
#define _FLAGVERTEX_H

#include "PaddedQVector3D.h"
#include <QVector2D>

struct FlagVertex
{
    PaddedQVector3D position;
    PaddedQVector3D normal;
    QVector2D       texcoord;
    GLfloat         shininess;
    GLubyte         specular[4];
};


#endif
