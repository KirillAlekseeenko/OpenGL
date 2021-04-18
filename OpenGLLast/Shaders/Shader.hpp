//
//  Shader.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <memory>

class Shader
{
public:
    
    Shader();
    Shader(GLenum shader_type, const std::string &filename);
    //Shader(GLenum shader_type, std::string shader_contents);
    
    GLuint get_handle() const
    {
        return handle;
    }
    
    bool is_compiled() const
    {
        return compiled;
    }
    
    Shader(const Shader& s) = delete;
    Shader& operator=(const Shader& s) = delete;
    
    Shader(Shader&& s);
    Shader& operator=(Shader&& s);
    
    ~Shader();
    
    std::pair<GLint, std::basic_string<GLchar>> compile();
    
private:
    GLuint handle = 0;
    bool compiled = false;
    
    void gl_source(GLenum shader_type, std::vector<std::string> contents);
};

#endif /* Shader_hpp */
