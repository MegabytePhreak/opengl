#ifndef _GLWIDGET_H
#define _GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtGui>

class GLWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLWidget(QWidget *parent = NULL );
    ~GLWidget();

protected:
    GLuint make_buffer(GLenum target, const void * data, GLsizei size);
    GLuint make_texture(const QString& filename);
};

#endif  /* _GLWIDGET_H */
