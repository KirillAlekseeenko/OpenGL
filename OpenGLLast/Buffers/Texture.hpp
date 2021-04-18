//
//  Texture.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.04.2021.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Texture
{
public:
    Texture();
    ~Texture();
    
    Texture(std::string path);
    
    Texture(const Texture& t) = delete;
    Texture& operator=(const Texture& t) = delete;
    
    Texture(Texture&& t);
    Texture& operator=(Texture&& t);
    
    Texture& set_texture_data(std::string s);
    
    Texture& set_wrap_s(GLint type);
    Texture& set_wrap_t(GLint type);
    
    Texture& set_min_filter(GLint type);
    Texture& set_mag_filter(GLint type);
    
    bool is_valid() {return data != nullptr;}
    
    GLuint get_handle() const { return handle; }                                 // TODO: create abstract opengl object
private:
    
    GLuint handle = 0;
    GLenum target = 0;
    
    unsigned char* data = nullptr;
    
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    
private:
    
    void binded(std::function<void(void)> action)
    {
        glBindTexture(GL_TEXTURE_2D, handle);
        
        action();
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    
};

#endif /* Texture_hpp */
