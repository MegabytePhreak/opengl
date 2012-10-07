#ifndef _GLFADERWIDGET_H
#define _GLFADERWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtGui>

class GLFaderWidget : public QGLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLFaderWidget(QWidget *parent ,QString& vertex_shader);
    ~GLFaderWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
protected slots:
    void onIdle();

private:

    bool make_resources();
    void update_fade_factor();
    GLuint make_buffer(GLenum target, const void * data, GLsizei size);
    GLuint make_texture(const QString& filename);
    GLuint make_shader(GLenum type, const QString& filename);
    GLuint make_program( GLuint vertex_shader, GLuint fragement_shader);

    void show_info_log(GLuint object,
        PFNGLGETSHADERIVPROC glGet_iv, 
        PFNGLGETSHADERINFOLOGPROC glGet_InfoLog);

    struct t_resources * resources;
    QTimer*  idle_timer;
    QTime    time;
    QString& vertex_shader;
    int      last_time;
};

#endif  /* _GLFADERWIDGET_H */
