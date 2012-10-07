#include <QtGui/QApplication>
#include <QtOpenGL/QGLWidget>
#include "GLFaderWidget.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    QString vertex_shader("../fader.v.glsl");
    if( argc > 1) 
        vertex_shader = argv[1];

    GLFaderWidget window(NULL,vertex_shader);
    window.resize(400,300);
    window.show();

    return app.exec();
}
