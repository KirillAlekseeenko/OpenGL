//
//  ShaderProgram.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(ShaderProgram&& s)
{
    handle = s.handle;
    s.handle = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& s)
{
    if (handle != s.handle)
    {
        for (const auto& c : pipeline)
        {
            glDetachShader(handle, c.get_handle());
        }
        
        glDeleteProgram(handle);
    }
    
    handle = s.handle;
    s.handle = 0;
    
    return *this;
}

ShaderProgram::~ShaderProgram()
{
    if (handle == 0) return;
    
    for (const auto& c : pipeline)
    {
        glDetachShader(handle, c.get_handle());
    }
    
    glDeleteProgram(handle);
}

std::pair<GLint, std::basic_string<GLchar>> ShaderProgram::link()
{
    for (auto& c : pipeline)
    {
        if (!c.is_compiled())
        {
            auto compile_result = c.compile();
            if (std::get<0>(compile_result) == GL_FALSE)
            {
                return compile_result;
            }
        }
    }
    
    glLinkProgram(handle);
    
    GLint link_status = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &link_status);
    
    std::basic_string<GLchar> log_str;
    
    if (link_status == GL_FALSE)
    {
        GLint log_size = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_size);
        
        std::vector<GLchar> log(log_size);
        
        glGetProgramInfoLog(handle, log_size, &log_size, log.data());
        
        std::copy(log.begin(), log.end(), std::back_inserter(log_str));
        
        std::cout << "\nShader compile error: \n" << log_str << "\n";
    }
    else
    {
        linked = true;
    }
    
    return std::pair<GLint, std::basic_string<GLchar>>{link_status, log_str};
}

GLint ShaderProgram::get_uniform_location(std::string name) const
{
    return glGetUniformLocation(handle, name.c_str());
}

bool ShaderProgram::use()
{
    if (!linked) return false;
    
    glUseProgram(handle);
    
    return true;
}

ShaderProgram& ShaderProgram::set_projection_mat(glm::mat4 m)
{
    auto proj_mat_handle = get_uniform_location("projection");
    glUniformMatrix4fv(proj_mat_handle, 1, GL_FALSE, glm::value_ptr(m));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_view_mat(glm::mat4 m)
{
    auto view_mat_handle = get_uniform_location("view");
    glUniformMatrix4fv(view_mat_handle, 1, GL_FALSE, glm::value_ptr(m));
    
    return *this;
}
