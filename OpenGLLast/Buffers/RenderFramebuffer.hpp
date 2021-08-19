//
//  RenderFramebuffer.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.05.2021.
//

#ifndef RenderFramebuffer_hpp
#define RenderFramebuffer_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

class RenderFramebuffer                                                     // for now it's just copypast of Framebuffer
{
public:
    RenderFramebuffer();
    ~RenderFramebuffer();
    
    RenderFramebuffer(const RenderFramebuffer& f) = delete;
    RenderFramebuffer& operator=(const RenderFramebuffer& f) = delete;
    
    RenderFramebuffer(RenderFramebuffer&& f);
    RenderFramebuffer& operator=(RenderFramebuffer&& f);
    
    void use_binded(GLenum target, std::function<void(void)> f);
private:
    GLuint handler = 0;
};

#endif /* RenderFramebuffer_hpp */
