//
//  RenderFramebuffer.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.05.2021.
//

#include "RenderFramebuffer.hpp"

RenderFramebuffer::RenderFramebuffer()
{
    glGenRenderbuffers(1, &handler);
}

RenderFramebuffer::~RenderFramebuffer()
{
    glDeleteRenderbuffers(1, &handler);
}

RenderFramebuffer::RenderFramebuffer(RenderFramebuffer&& f) : handler{f.handler}
{
    f.handler = 0;
}

RenderFramebuffer& RenderFramebuffer::operator=(RenderFramebuffer&& f)
{
    this->~RenderFramebuffer();
    
    handler = f.handler;
    f.handler = 0;
    
    return *this;
}

void RenderFramebuffer::use_binded(GLenum target, std::function<void(void)> f)
{
    glBindRenderbuffer(target, handler);
    
    f();
    
    glBindRenderbuffer(target, 0);             // get back to default framebuffer
}
