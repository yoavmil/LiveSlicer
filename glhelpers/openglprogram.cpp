#include "openglprogram.h"
#include "logger.h"

VertexAttrib::VertexAttrib(GLint _id)
{
    setDefaults();
    id = _id;
}

VertexAttrib::VertexAttrib(const char *_name)
{
    setDefaults();
    name = _name;
}

OpenGLShader::OpenGLShader(const char *shader, ShaderType _shaderType):
    type(_shaderType),
    id(0),
    shaderCode(shader)
{
    initializeOpenGLFunctions();
}

OpenGLShader::~OpenGLShader()
{
    if (Compiled()) {
        //TODO delete object
    }
}

bool OpenGLShader::Build()
{
    bool ok = true;
    id = glCreateShader((GLenum)GetShaderType());
    const char* str = Code().c_str();
    glShaderSource(id, 1, &str, NULL);
    glCompileShader(id);
    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> log;
        log.resize(infoLogLength);

        glGetShaderInfoLog(id, infoLogLength, NULL, log.data());
        WRNF << "failed to compile \n" << log.data();
        ok = false;
    }
    return ok;
}


OpenGLProgram::OpenGLProgram()
{
    initializeOpenGLFunctions();
    programId = glCreateProgram();
}

OpenGLProgram::~OpenGLProgram()
{

}

bool OpenGLProgram::AddShader(OpenGLShader &shader)
{
    if (!shader.Compiled())
        shader.Build();
    if (!shader.Compiled())
        return false;

    glAttachShader(programId, shader.GetID());
    return true;
}

bool OpenGLProgram::Build()
{
    glLinkProgram(programId);
    GLint status;
    glGetProgramiv (programId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> log;
        log.resize(infoLogLength);

        glGetProgramInfoLog(programId, infoLogLength, NULL, log.data());
        WRNF << "failed to bind \n" << log.data();
        return false;
    }
    return true;
}

void OpenGLProgram::Use()
{
    glUseProgram(programId);
}

GLint OpenGLProgram::AttribLocation(const char *attrib)
{
    return glGetAttribLocation(programId, attrib);
}

GLint OpenGLProgram::UniformLocation(const char *uniform)
{
    return glGetUniformLocation(programId, uniform);
}







