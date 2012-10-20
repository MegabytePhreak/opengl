#ifndef _GLPROGRAM_H
#define _GLPROGRAM_H

#include <QString>
#include <GL/glew.h>


class GLProgram
{   
    public:
    static GLProgram fromStrings(
        const QString& vertex_shader_str, 
        const QString& fragment_shader_str
    );


    static GLProgram fromFiles(
        const QString& vertex_shader_filename,
        const QString& fragment_shader_filename
    );

    bool    ok();

    GLint   getUniformLocation(const QString& name) const;
    GLint   getAttributeLocation(const QString& name) const;
    
    ~GLProgram();

    protected:    
    GLProgram( 
        const QByteArray& vertex_shader_buf, 
        const QByteArray& fragment_shader_buf
    );
    
    GLuint  vertex_shader;
    GLuint  fragment_shader;
    GLuint  program;

    GLuint make_shader(GLenum type, const QByteArray& buf);
    GLuint make_program( GLuint vertex_shader, GLuint fragement_shader);

    void show_info_log(GLuint object,
        PFNGLGETSHADERIVPROC glGet_iv, 
        PFNGLGETSHADERINFOLOGPROC glGet_InfoLog);

};

#endif
