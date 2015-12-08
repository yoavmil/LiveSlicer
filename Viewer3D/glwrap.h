#ifndef GL_H
#define GL_H
#include <QOpenGLFunctions>
#include "glm/mat4x4.hpp"

//just a wrapper for OpenGL functions,
//  to not expose the entire OpenGL API,
//  and to wrap glm objects
enum class GLCap {
    CullFaces = GL_CULL_FACE,
    DepthTest = GL_DEPTH_TEST,
    Lighting = GL_LIGHTING,
};

class GLWrap {
public:
    void Init(); //must call this function on initializeGL()

    void Clear(GLbitfield mask);
    void Viewport(GLint x,GLint y,GLsizei width,GLsizei height);
    void UniformMatrix(GLint location, const glm::mat4& mat);
    void UniformMatrix(GLint location, const glm::mat3& mat);
    void Uniform(GLint location, const glm::vec3& vec);
    void Uniform(GLint location, const GLfloat& val);
    void ClearColor(const QColor& color);
    void Enable(GLCap cap, bool enable = true);

    //buffers
    void GenBuffers(int count, GLuint* id);
    GLuint GenBuffer();
    void BindArrayBuffer(GLuint id);
    void BindElementArrayBuffer(GLuint id);
    void ArrayBufferData(GLuint byteSize, const void* data, GLenum usage = GL_STATIC_DRAW);
    void ElementArrayBufferData(GLuint byteSize, const void* data, GLenum usage = GL_STATIC_DRAW);
    void EnableVertexAttribArray(GLuint index, bool enable = true);
    void VertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLuint offset);


    //mayabe delete this
    void DrawArrays(GLenum mode, GLint first, GLsizei count);
private:
    QOpenGLFunctions gl;
    void checkError(const char* funcName = NULL);
};

#endif // GL_H
