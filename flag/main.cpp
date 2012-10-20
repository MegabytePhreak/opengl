#include <QtGui/QApplication>
#include <QtOpenGL/QGLWidget>
#include "GLFlagWidget.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    GLFlagWidget window;
    window.resize(400,300);
    window.show();

    return app.exec();
}