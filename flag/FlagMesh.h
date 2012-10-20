#ifndef _FLAGMESH_H
#define _FLAGMESH_H

#include "GLMesh.h"
#include <QVector>
#include "FlagVertex.h"

class FlagMesh : GLMesh 
{
public:
    FlagMesh();

    void update(GLfloat time);

private:
    void calculate_flag_vertex(
            FlagVertex& vertex, GLfloat s, GLfloat t, GLfloat time);
    QVector<FlagVertex> verticies;
    
};


#endif //_FLAGMESH_H
