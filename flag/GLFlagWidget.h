#ifndef _GLFLAGWIDGET_H
#define _GLFLAGWIDGET_H

#include "GLWidget.h"

class GLFlagWidget : public GLWidget {

    Q_OBJECT // must include this if you use Qt signals/slots

public:
    GLFlagWidget(QWidget *parent = NULL );
    ~GLFlagWidget();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    
private slots:
    void onIdle();

private:

    bool make_resources();

    struct t_resources * resources;
    QTimer*  idle_timer;
    QTime    time;
    int      last_time;
};

#endif  /* _GLFLAGWIDGET_H */
