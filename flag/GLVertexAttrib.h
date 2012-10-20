#ifndef _GLVERTEXATTRIB_H
#define _GLVERTEXATTRIB_H

#include <GL/gl.h>
#include <QString>

struct GLVertexAttrib 
{
    GLuint      index;
    QString     name;
    GLint       size;
    GLenum      type;
    GLboolean       normalized;
    GLsizei         stride;
    const GLvoid *  pointer;
};

#endif
