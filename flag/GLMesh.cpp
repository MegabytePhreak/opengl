
#include "GLMesh.h"
#include <GL/glew.h>


void GLMesh::render()
{
    glBindTexture(GL_TEXTURE_2D,texture);
    glBindBuffer(GL_ARRAY_BUFFER,vertex_buffer);
    
    QVector<GLVertexAttrib>::const_iterator it;
    for(it = attributes.constBegin(); it != attributes.constEnd(); it++)
    {
        glVertexAttribPointer(
            it->index, it->size, it->type, it->normalized, 
            it->stride, it->pointer);

    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer);

    glDrawElements( 
        GL_TRIANGLES, 
        element_count,
        GL_UNSIGNED_SHORT,
        (void *) 0 
    );

}

void GLMesh::updateAttributes(const GLProgram& program)
{
    QVector<GLVertexAttrib>::iterator attr;
    for(attr = attributes.begin(); attr != attributes.end(); attr++ )
    {
        attr->index = program.getAttributeLocation(attr->name);
    }
}

    GLMesh::GLMesh()
{
}



