#include <QtGui/QMouseEvent>
#include <QtGui>
#include <QtDebug>
#include "GL/glew.h"
#include "GLFaderWidget.h"
#include "stdio.h"

struct t_resources{
    
    GLuint vertex_buffer;
    GLuint element_buffer;
    GLuint textures[2];

    /* ... fields for buffer and texture objects */
    GLuint vertex_shader, fragment_shader, program;
    
    struct {
        GLint timer;
        GLint textures[2];
    } uniforms;

    struct {
        GLint position;
    } attributes;

    GLfloat timer;
};

const static GLfloat vertex_buffer_data[] =
{
    -1.0f, -1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 0.0f, 1.0f,
};

const static GLushort element_buffer_data[] = {0,1,2,3};

GLFaderWidget::GLFaderWidget(QWidget *parent,QString& vertex_shader)
    : QGLWidget(parent),resources(NULL),time(),last_time(0),vertex_shader(vertex_shader)
{
    setMouseTracking(true);
    idle_timer = new QTimer(this);
    connect(idle_timer,SIGNAL(timeout()),this,SLOT(onIdle()));
    time.start();
    last_time = time.elapsed();

}

GLFaderWidget::~GLFaderWidget()
{
    if(resources)
        delete resources;
}


void GLFaderWidget::initializeGL() {
    
    glewInit();
	if(!GLEW_VERSION_2_0)
	{
        printf("OpenGL Version 2.0 not available\n");
        exit(1);
	}
	
    if(!make_resources())
	{
	    printf("Resource loading failed\n");
	    exit(1);
    }

    idle_timer->start(10);
}

void GLFaderWidget::resizeGL(int w, int h) {
    printf("Resizing\n");
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*gluOrtho2D(0, w, 0, h); // set origin to bottom left corner*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void GLFaderWidget::paintGL() {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(resources->program);
    glUniform1f(resources->uniforms.timer,resources->timer);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, resources->textures[0]);
    glUniform1i(resources->uniforms.textures[0],0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, resources->textures[1]);
    glUniform1i(resources->uniforms.textures[1],1);

    glBindBuffer(GL_ARRAY_BUFFER,resources->vertex_buffer);
    glVertexAttribPointer(
            resources->attributes.position, 
            4,
            GL_FLOAT,
            false,
            sizeof(GLfloat)*4,
            (void*)0
        );
    glEnableVertexAttribArray(resources->attributes.position);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,resources->element_buffer);
    glDrawElements(
            GL_TRIANGLE_STRIP, 
            4, 
            GL_UNSIGNED_SHORT, 
            (void*)0
        );

    glDisableVertexAttribArray(resources->attributes.position);

}

void GLFaderWidget::onIdle(){
    int this_time = time.elapsed();
    resources->timer = this_time * 0.001f;
    /*printf("Frame time: %d\n",this_time-last_time);*/
    last_time = this_time;
    update();
}

void GLFaderWidget::mousePressEvent(QMouseEvent *event) {

}
void GLFaderWidget::mouseMoveEvent(QMouseEvent *event) {
    //printf("%d, %d\n", event->x(), event->y());
}

void GLFaderWidget::keyPressEvent(QKeyEvent* event) {
    switch(event->key()) {
    case Qt::Key_Escape:
        close();
        break;
    default:
        event->ignore();
        break;
    }
}

bool GLFaderWidget::make_resources()
{
    resources = new struct t_resources;

    if(!resources)
        return false;

    resources->timer = 0.0f;

    resources->vertex_buffer = make_buffer(GL_ARRAY_BUFFER,
            vertex_buffer_data, sizeof(vertex_buffer_data));
    resources->element_buffer = make_buffer(GL_ELEMENT_ARRAY_BUFFER,
            element_buffer_data, sizeof(element_buffer_data));

    resources->textures[0] = make_texture(QString("../hello1.png"));
    resources->textures[1] = make_texture(QString("../hello2.png"));
    
    if( resources->textures[0]==0 || resources->textures[1]==0)
        return false;

    resources->vertex_shader = make_shader(GL_VERTEX_SHADER,vertex_shader);
    resources->fragment_shader = make_shader(GL_FRAGMENT_SHADER,"../fader.f.glsl");

    if( resources->vertex_shader == 0 || resources->fragment_shader == 0)
        return false;

    resources->program = make_program(resources->vertex_shader,
            resources->fragment_shader);

    resources->uniforms.timer = 
        glGetUniformLocation( resources->program, "timer");
    resources->uniforms.textures[0] = 
        glGetUniformLocation( resources->program, "textures[0]");
    resources->uniforms.textures[1] = 
        glGetUniformLocation( resources->program, "textures[1]");

    resources->attributes.position = 
        glGetAttribLocation(resources->program, "position");
    


    return true;        
}

GLuint GLFaderWidget::make_buffer(GLenum target,
        const void * data, GLsizei size)
{
    GLuint buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(target,buffer);
    glBufferData(target,size,data,GL_STATIC_DRAW);
    return buffer;

}

GLuint GLFaderWidget::make_texture(const QString& filename)
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

GLuint GLFaderWidget::make_shader(GLenum type, const QString& filename)
{
    GLuint shader;
    QFile file(filename);
    GLint shader_ok;
    

    if(!file.open(QIODevice::ReadOnly))
        return 0;

    QByteArray data = file.readAll();
    GLint size = file.size();
    file.close();

    const char * contents = data.constData();

    printf("%s\n",contents);

    shader = glCreateShader(type);
    glShaderSource(shader,1,(const GLchar**)&contents,&size);
    glCompileShader(shader);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&shader_ok);
    if(!shader_ok) 
    {
        qCritical() << "Failed to compile shader" << filename;
        show_info_log(shader,glGetShaderiv,glGetShaderInfoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint GLFaderWidget::make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint program_ok;

    GLuint program = glCreateProgram();
    
    glAttachShader(program,vertex_shader);
    glAttachShader(program,fragment_shader);
    glLinkProgram(program);

    glGetProgramiv(program,GL_LINK_STATUS,&program_ok);
    if(!program_ok)
    {
        qCritical() << "Failed to link shader program";
        show_info_log(program,glGetProgramiv,glGetProgramInfoLog);
        glDeleteProgram(program);
        
        return 0;
    }
    return program;

}

void GLFaderWidget::show_info_log(GLuint object,
        PFNGLGETSHADERIVPROC glGet_iv, PFNGLGETSHADERINFOLOGPROC glGet_InfoLog)
{
    GLint log_length;
    
    glGet_iv(object,GL_INFO_LOG_LENGTH, &log_length);
    char * log = new char[log_length];
    glGet_InfoLog(object, log_length, NULL, log);
    qDebug(log);

    delete log;
}


