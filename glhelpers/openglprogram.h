#ifndef OPENGLPROGRAM_H
#define OPENGLPROGRAM_H

#include <QGLFunctions>
#include <vector>
#include <string>

enum class ShaderType
{
    Vertex = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER,
};

class OpenGLShader: protected QOpenGLFunctions
{
public:
    OpenGLShader(const char* shader, ShaderType _shaderType);
    ~OpenGLShader();

    bool Build();
    GLuint GetID() {return id;}
    ShaderType GetShaderType() {return type;}
    const std::string& Code() {return shaderCode;}
    bool Compiled() { return id > 0;}
private:
    ShaderType type;
    GLuint id;
    std::string shaderCode;
};

class VertexAttrib
{
    enum class DataType {
        Float = GL_FLOAT,
        UByte = GL_UNSIGNED_BYTE
    };

    VertexAttrib(GLint _id);
    VertexAttrib(const char* _name);

    DataType dataType;
    int size;//number of data elements, not byte size
    bool normelize;
    GLsizei stride;//the entire data size in bytes
    GLsizei offset;//the offset of this attrib
    void setDefaults()
    {
        id = -1;
        dataType = DataType::Float;
        size = 3;
        normelize = false;
        stride = 3*sizeof(GLfloat);
        offset = 0;
    }
    GLint id;
    std::string name;
};

class OpenGLProgram: protected QOpenGLFunctions
{
public:
    OpenGLProgram();
    ~OpenGLProgram();
    bool AddShader(OpenGLShader& shader);
    bool BindShaders();
    bool Build();
    void Use();
    void Release();
    GLint AttribLocation(const char* attrib);
    GLint UniformLocation(const char* uniform);
    void EnableAttrib(const char* attrib, bool enable = true);
    void EnableAttrib(GLint id, bool enable = true);
    void AddVertexAttribPointer(const VertexAttrib& attrib);
    VertexAttrib& GetVertexAttrib(GLint id);
    VertexAttrib& GetVertexAttrib(const char* id);
    std::vector<VertexAttrib> attribs;
    std::vector<OpenGLShader> shaders;
private:
    GLuint programId;
};

#endif // OPENGLPROGRAM_H
