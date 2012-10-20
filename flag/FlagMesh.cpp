
#include "FlagMesh.h"

#define FLAG_X_RES 100
#define FLAG_Y_RES 75
#define FLAG_S_STEP (1.0f/((GLfloat)(FLAG_X_RES - 1)))
#define FLAG_T_STEP (1.0f/((GLfloat)(FLAG_Y_RES - 1)))
#define FLAG_VERTEX_COUNT (FLAG_X_RES * FLAG_Y_RES)

FlagMesh::FlagMesh()
    :verticies(FLAG_VERTEX_COUNT)
{
    QVector<GLushort> element_data;
    GLsizei s,t;
    GLushort index;

    QVector<FlagVertex>::iterator vertex = verticies.begin();
    for(GLsizei t = 0; t < FLAG_Y_RES; t++)
    {
        for(GLsizei s = 0; s < FLAG_X_RES; s++)
        {
            GLfloat ss = FLAG_S_STEP * s;
            GLfloat tt = FLAG_T_STEP * t;

            calculate_flag_vertex(*vertex,ss,tt,0.0f);
            vertex->texcoord = QVector2D(ss,tt);
            vertex->shininess = 0.0f;
            vertex->specular[0] = 0;
            vertex->specular[1] = 0;
            vertex->specular[2] = 0;
            vertex->specular[3] = 0;

        }
    }


}
void FlagMesh::calculate_flag_vertex(
    FlagVertex& vertex, GLfloat s, GLfloat t, GLfloat time)
{
    
}

