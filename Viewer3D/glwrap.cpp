#include <QColor>
#include <QOpenGLFunctions>
#include "glwrap.h"
#include "utils.h"
#include <glm/gtc/type_ptr.hpp>
//#define CHECK_ERROR checkError(__FUNCTION__);
#define CHECK_ERROR
void GLWrap::Init()
{
    gl.initializeOpenGLFunctions();
    CHECK_ERROR
}

void GLWrap::Clear(GLbitfield mask)
{
    gl.glClear(mask);
    CHECK_ERROR
}

void GLWrap::Viewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    gl.glViewport(x, y, width, height);
    CHECK_ERROR
}

void GLWrap::UniformMatrix(GLint location, const glm::mat4 &mat)
{    
    gl.glUniformMatrix4fv(location, 1, false, glm::value_ptr(mat));
    CHECK_ERROR
}

void GLWrap::UniformMatrix(GLint location, const glm::mat3 &mat)
{
    gl.glUniformMatrix3fv(location, 1, false, glm::value_ptr(mat));
    CHECK_ERROR
}

void GLWrap::ClearColor(const QColor &color)
{
    gl.glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void GLWrap::Enable(GLCap cap, bool enable)
{
    if (enable)
        gl.glEnable((GLenum)cap);
    else
        gl.glDisable((GLenum)cap);
    CHECK_ERROR
}

void GLWrap::GenBuffers(int count, GLuint *id)
{
    gl.glGenBuffers(count, id);
    CHECK_ERROR
}

GLuint GLWrap::GenBuffer()
{
    GLuint id;
    GenBuffers(1, &id);
    return id;
}

void GLWrap::BindArrayBuffer(GLuint id)
{
    gl.glBindBuffer(GL_ARRAY_BUFFER, id);
    CHECK_ERROR
}

void GLWrap::BindElementArrayBuffer(uint id)
{
    gl.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    CHECK_ERROR
}

void GLWrap::ArrayBufferData(GLuint byteSize, const void *data, GLenum usage)
{
    gl.glBufferData(GL_ARRAY_BUFFER, byteSize, data, usage);
    CHECK_ERROR
}

void GLWrap::ElementArrayBufferData(GLuint byteSize, const void *data, GLenum usage)
{
    gl.glBufferData(GL_ELEMENT_ARRAY_BUFFER, byteSize, data, usage);
    CHECK_ERROR
}

void GLWrap::EnableVertexAttribArray(GLuint index, bool enable)
{
    if (enable)
        gl.glEnableVertexAttribArray(index);
    else
        gl.glDisableVertexAttribArray(index);
    CHECK_ERROR
}

void GLWrap::VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint offset)
{
    gl.glVertexAttribPointer(indx, size, type, normalized, stride, (char*)NULL + (offset));
    CHECK_ERROR
}

void GLWrap::DrawArrays(GLenum mode, GLint first, GLsizei count)
{
    gl.glDrawArrays(mode, first, count);
    CHECK_ERROR
}

void GLWrap::checkError(const char *funcName)
{
    GLenum glError;
    while((glError = gl.glGetError()) != GL_NO_ERROR) {
        if (funcName == NULL)
            DBGF << _S(glError);
        else
            qDebug() << funcName << "glError" << QString("%1").arg(glError, 0, 16);
    }    
}

