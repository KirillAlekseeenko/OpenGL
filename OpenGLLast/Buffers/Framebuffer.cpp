//
//  Framebuffer.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.05.2021.
//

#include "Framebuffer.hpp"

#include "ITexture.hpp"

Framebuffer::Framebuffer()
{
    glGenFramebuffers(1, &handler);
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &handler);
}

Framebuffer::Framebuffer(Framebuffer&& f) : handler{f.handler}
{
    f.handler = 0;
}

Framebuffer& Framebuffer::operator=(Framebuffer&& f)
{
    this->~Framebuffer();
    
    handler = f.handler;
    f.handler = 0;
    
    return *this;
}

void Framebuffer::attach_texture(std::shared_ptr<ITexture> t, GLenum attachment)
{
    use_binded(GL_FRAMEBUFFER, [&t, attachment]()
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, t->get_handle(), 0);         // TODO: adapt for cubemap
    });
}

void Framebuffer::use_binded(GLenum target, std::function<void(void)> f)
{
    glBindFramebuffer(target, handler);
    
    f();
    
    glBindFramebuffer(target, 0);             // get back to default framebuffer
}
