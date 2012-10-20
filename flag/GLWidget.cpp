#include <QtGui>
#include <QtDebug>
#include "GL/glew.h"
#include "GLWidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
}

GLWidget::~GLWidget()
{
}

GLuint GLWidget::make_buffer(GLenum target,
        const void * data, GLsizei size)
{
    GLuint buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(target,buffer);
    glBufferData(target,size,data,GL_STATIC_DRAW);
    return buffer;

}

GLuint GLWidget::make_texture(const QString& filename)
{

    GLuint texture;
    int width, height;
    void * pixels;


    QImage image = QImage(filename);

    if(image.isNull())
        return 0;

    QImage tex = convertToGLFormat(image);
    
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D, 0,           /* target, level of detail */
        GL_RGB8,                    /* internal format */
        tex.width(),tex.height(), 0,           /* width, height, border */
        GL_RGBA, GL_UNSIGNED_BYTE,   /* external format, type */
        tex.constBits()                      /* pixels */
    );
    return texture;
}


