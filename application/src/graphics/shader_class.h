#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader(const std::string& shader_file_path);
    void UserProgram()const { glUseProgram(this->m_programHandle); }
private:
    struct VertexFragmentShaderHandlePair
    {
        GLint vertex_shader_handle;
        GLint fragment_shader_handle;
    };
private:
    VertexFragmentShaderHandlePair ReadShader(const std::string& shader_file_path);
    GLint CompileShader(const std::string& shader_source, GLenum shader_type);
    bool IsShaderCompiledSuccessfully(GLuint shader_handle);
    bool IsProgramLinkedSuccessfully();
private:
    GLint m_programHandle = -1;
private:
    static GLint s_InvalidProgramHandle;
};