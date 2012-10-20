
#include "GLProgram.h"
#include <QtDebug>
#include <QFile>


GLProgram GLProgram::fromStrings(
        const QString& vertex_shader_str,
        const QString& fragment_shader_str
    )
{
    QByteArray vertex_shader_buf = vertex_shader_str.toAscii();
    QByteArray fragment_shader_buf = fragment_shader_str.toAscii();

    return GLProgram(vertex_shader_buf,fragment_shader_buf);
}

GLProgram GLProgram::fromFiles( 
        const QString& vertex_shader_filename,
        const QString& fragment_shader_filename
    )
{
    QByteArray vertex_shader_buf;
    QByteArray fragment_shader_buf;

    QFile   vertex_shader_file(vertex_shader_filename);
    QFile   fragment_shader_file(fragment_shader_filename);

    if(vertex_shader_file.open(QIODevice::ReadOnly))
    {
        vertex_shader_buf = vertex_shader_file.readAll();
        vertex_shader_file.close();
    }

    if(fragment_shader_file.open(QIODevice::ReadOnly))
    {
        fragment_shader_buf = fragment_shader_file.readAll();
        fragment_shader_file.close();
    }
            

    return GLProgram(vertex_shader_buf,fragment_shader_buf);
}

        
        

GLProgram::GLProgram(
        const QByteArray& vertex_shader_buf, 
        const QByteArray& fragment_shader_buf
    )
   :vertex_shader(0),fragment_shader(0),program(0)
{
    vertex_shader = make_shader(GL_VERTEX_SHADER,vertex_shader_buf);
    if(!vertex_shader)
        return;
    
    fragment_shader = make_shader(GL_FRAGMENT_SHADER,fragment_shader_buf);
    if(!fragment_shader)
        return;

    program = make_program(vertex_shader,fragment_shader);
    if(!program) 
        return;

}

GLProgram::~GLProgram()
{
    glDetachShader(program,vertex_shader);
    glDetachShader(program,fragment_shader);

    glDeleteProgram(program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

}

bool GLProgram::ok()
{
    return vertex_shader && fragment_shader && program;
}

GLint   GLProgram::getUniformLocation(const QString& name) const
{
    QByteArray ascii = name.toAscii();

    return glGetUniformLocation(program, ascii);

}

GLint   GLProgram::getAttributeLocation(const QString& name) const
{
    QByteArray  ascii = name.toAscii();

    return glGetAttribLocation(program, ascii);
}


GLuint GLProgram::make_shader(GLenum type, const QByteArray& buf)
{
    GLint  shader_ok;
    GLuint shader;

    const char * contents = buf.constData();
    GLint   size = buf.size();

    shader = glCreateShader(type);
    glShaderSource(shader,1,(const GLchar**)&contents,&size);
    glCompileShader(shader);
    glGetShaderiv(shader,GL_COMPILE_STATUS,&shader_ok);
    if(!shader_ok) 
    {
        show_info_log(shader,glGetShaderiv,glGetShaderInfoLog);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint GLProgram::make_program(GLuint vertex_shader, GLuint fragment_shader)
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


void GLProgram::show_info_log(GLuint object,
        PFNGLGETSHADERIVPROC glGet_iv, PFNGLGETSHADERINFOLOGPROC glGet_InfoLog)
{
    GLint log_length;
    
    glGet_iv(object,GL_INFO_LOG_LENGTH, &log_length);
    char * log = new char[log_length];
    glGet_InfoLog(object, log_length, NULL, log);
    qDebug() << log;

    delete log;
}


