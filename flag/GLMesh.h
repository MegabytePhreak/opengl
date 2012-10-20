#ifndef _GLMESH_H
#define _GLMESH_H

#include <GL/glew.h>
#include <QVector>
#include "GLVertexAttrib.h"
#include "GLProgram.h"

class GLMesh 
{
public:
    void render();
    void updateAttributes(const GLProgram & program);

    GLuint vertex_buffer;
    GLuint element_buffer;
    GLsizei element_count;
    GLuint  texture;
    QVector<GLVertexAttrib> attributes;
protected:
    GLMesh();

};

#endif

