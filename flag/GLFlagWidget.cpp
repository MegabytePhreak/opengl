#include <QtGui/QMouseEvent>
#include <QtGui>
#include <QtDebug>
#include "GL/glew.h"
#include "GLFlagWidget.h"
#include "stdio.h"
#include "PaddedQVector3D.h"

    
GLFlagWidget::GLFlagWidget(QWidget *parent)
    : GLWidget(parent),resources(NULL),time(),last_time(0)
{

}

GLFlagWidget::~GLFlagWidget()
{

}


void GLFlagWidget::initializeGL() {

}

void GLFlagWidget::resizeGL(int w, int h) {

}

void GLFlagWidget::paintGL() {


}

void GLFlagWidget::onIdle(){
}

void GLFlagWidget::mousePressEvent(QMouseEvent *event) {

}
void GLFlagWidget::mouseMoveEvent(QMouseEvent *event) {
    //printf("%d, %d\n", event->x(), event->y());
}

void GLFlagWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}

bool GLFlagWidget::make_resources()
{
       
}


