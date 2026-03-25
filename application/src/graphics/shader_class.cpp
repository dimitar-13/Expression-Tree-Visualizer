#include "shader_class.h"
#include<iostream>
#include <fstream>

GLint Shader::s_InvalidProgramHandle = -1;

Shader::Shader(const std::string& shader_file_path)
{
    VertexFragmentShaderHandlePair shaders = this->ReadShader(shader_file_path);

    this->m_programHandle = glCreateProgram();

    glAttachShader(this->m_programHandle,shaders.vertex_shader_handle);
    glAttachShader(this->m_programHandle, shaders.fragment_shader_handle);

    glLinkProgram(this->m_programHandle);

    if (!this->IsProgramLinkedSuccessfully())
    {
        this->m_programHandle = Shader::s_InvalidProgramHandle;
        return;
    }
    glDetachShader(this->m_programHandle, shaders.vertex_shader_handle);
    glDetachShader(this->m_programHandle, shaders.fragment_shader_handle);

    glDeleteShader(shaders.vertex_shader_handle);
    glDeleteShader(shaders.fragment_shader_handle);

}

void Shader::SetUniform2D(const std::string& uniform_name, Position2D value)
{
    int uniform_location = GetUniformLocationByName(uniform_name);

    glUniform2fv(uniform_location, 1, value[0]);
}

Shader::VertexFragmentShaderHandlePair Shader::ReadShader(const std::string& shader_file_path)
{
    const char* kVertexShaderIdentifier = "#Shader:Vertex";
    const char* kFragmentShaderIdentifier = "#Shader:Fragment";

    std::fstream shader_source_file(shader_file_path);
    VertexFragmentShaderHandlePair result;


    if (!shader_source_file.is_open())
    {
        std::cout << "Failed to open shader file at: " << shader_file_path << '\n';
        return VertexFragmentShaderHandlePair{ Shader::s_InvalidProgramHandle, Shader::s_InvalidProgramHandle };
    }

    int current_shader_type_array_index = -1;
    std::string current_shader_source_builder[2];
    std::string line;

    while (std::getline(shader_source_file, line))
    {
        if (line.find(kVertexShaderIdentifier) != std::string::npos)
        {
            current_shader_type_array_index = 0;
            continue;
        } 
        else if (line.find(kFragmentShaderIdentifier) != std::string::npos)
        {
            current_shader_type_array_index = 1;
            continue;
        }

        if (current_shader_type_array_index > -1)
        {
            current_shader_source_builder[current_shader_type_array_index] += line + '\n';
        }
    }

    result.vertex_shader_handle   =  this->CompileShader(current_shader_source_builder[0], GL_VERTEX_SHADER);
    result.fragment_shader_handle = this->CompileShader(current_shader_source_builder[1], GL_FRAGMENT_SHADER);


    return result;
}

GLint Shader::CompileShader(const std::string& shader_source, GLenum shader_type)
{
    GLuint result = glCreateShader(shader_type);
    const char* source = shader_source.c_str();
    glShaderSource(result, 1, &source, nullptr);
    glCompileShader(result);

    return this->IsShaderCompiledSuccessfully(result) ? result : Shader::s_InvalidProgramHandle;
}

bool Shader::IsShaderCompiledSuccessfully(GLuint shader_handle)
{
    int compileStatus;

    glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compileStatus);

    if (!compileStatus)
    {
        constexpr size_t kInfoLogBufferSize = 255;

        char infoLog[kInfoLogBufferSize];

        int shader_info_log_len;

        glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &shader_info_log_len);

        glGetShaderInfoLog(shader_handle, kInfoLogBufferSize * sizeof(infoLog[0]), &shader_info_log_len, infoLog);

        std::cout << "Shader compile error:" << infoLog << '\n';

        return false;
    }

    return true;
}

bool Shader::IsProgramLinkedSuccessfully()
{
    int program_link_status;

    glGetShaderiv(this->m_programHandle, GL_LINK_STATUS, &program_link_status);

    if (!program_link_status)
    {
        constexpr size_t kInfoLogBufferSize = 255;

        char infoLog[kInfoLogBufferSize];

        int program_info_log;

        glGetShaderiv(this->m_programHandle, GL_INFO_LOG_LENGTH, &program_info_log);

        glGetShaderInfoLog(this->m_programHandle, kInfoLogBufferSize * sizeof(infoLog[0]), &program_info_log, infoLog);

        std::cout << "Shader compile error:" << infoLog << '\n';

        return false;
    }

    return true;
}

int Shader::GetUniformLocationByName(const std::string& uniform_name)const
{
    int uniform = glGetUniformLocation(this->m_programHandle, uniform_name.c_str());

    if (uniform != -1)
    {
        std::cout << "Cant find uniform with name:" << uniform_name << '\n';
    }

    return uniform;
}
