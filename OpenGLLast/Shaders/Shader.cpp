//
//  Shader.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#include "Shader.hpp"

#include <exception>

Shader::Shader()
{
    handle = 0;
}
Shader::Shader(GLenum shader_type, const std::string &filename)
{
    std::ifstream in{filename};
    
    if (!in.is_open()) throw std::runtime_error{"file not found"};
    
    std::vector<std::string> contents;
    
    for (std::string line; std::getline(in, line);)
    {
        line.append("\n");
        contents.push_back(std::move(line));
    }
    
    gl_source(shader_type, std::move(contents));
}

Shader::Shader(Shader&& s)
{
    handle = s.handle;
    s.handle = 0;
}

Shader& Shader::operator=(Shader&& s)
{
    if (handle != s.handle)
    {
        glDeleteShader(handle);
    }
    
    handle = s.handle;
    s.handle = 0;
    
    return *this;
}

/*Shader::Shader(GLenum shader_type, std::string shader_contents)            TODO: shader factory
{
    gl_source(shader_type, std::move(shader_contents));
}*/

std::pair<GLint, std::basic_string<GLchar>> Shader::compile()
{
    glCompileShader(handle);
    
    GLint compile_success = 0;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compile_success);
    
    std::basic_string<GLchar> log_str;
    
    if (compile_success == GL_FALSE)
    {
        GLint log_size = 0;
        glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_size);
        
        std::vector<GLchar> log(log_size);
        
        glGetShaderInfoLog(handle, log_size, &log_size, log.data());
        
        std::copy(log.begin(), log.end(), std::back_inserter(log_str));
        
        std::cout << "\nShader compile error: \n" << log_str << "\n";
    }
    else
    {
        compiled = true;
    }
    
    return std::pair<GLint, std::basic_string<GLchar>>{compile_success, log_str};
}

Shader::~Shader()
{
    if (handle != 0)
    {
        glDeleteShader(handle);
    }
}

void Shader::gl_source(GLenum shader_type, std::vector<std::string> contents)
{
    std::vector<const char*> raw_strings;
    
    std::transform(
                   contents.begin(),
                   contents.end(),
                   std::back_inserter(raw_strings),
                   [] (const std::string &s) { return s.c_str(); });
    
    //auto raw_str = contents.c_str();
    
    handle = glCreateShader(shader_type);
    
    glShaderSource(
                   handle,
                   (int) raw_strings.size(),
                   raw_strings.data(),
                   NULL);                       // assume that our strings are null-terminated
    
}


