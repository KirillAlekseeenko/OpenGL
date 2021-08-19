//
//  Framebuffer.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.05.2021.
//

#ifndef Framebuffer_hpp
#define Framebuffer_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class ITexture;

class Framebuffer
{
public:
    Framebuffer();
    ~Framebuffer();
    
    Framebuffer(const Framebuffer& f) = delete;
    Framebuffer& operator=(const Framebuffer& f) = delete;
    
    Framebuffer(Framebuffer&& f);
    Framebuffer& operator=(Framebuffer&& f);
    
    void attach_texture(std::shared_ptr<ITexture> t, GLenum attachment);
    
    void use_binded(GLenum target, std::function<void(void)> f);
private:
    GLuint handler = 0;
};

#endif /* Framebuffer_hpp */
