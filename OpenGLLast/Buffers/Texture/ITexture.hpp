//
//  ITexture.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 29.05.2021.
//

#ifndef ITexture_hpp
#define ITexture_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

class ITexture
{
public:
    virtual void load_to_vram(GLenum type = GL_UNSIGNED_BYTE) = 0;
    virtual void set_wrap_s(GLint type) = 0;
    virtual void set_wrap_t(GLint type) = 0;
    virtual void set_wrap_r(GLint type) = 0;
    
    virtual void set_min_filter(GLint type) = 0;
    virtual void set_mag_filter(GLint type) = 0;
    
    virtual bool is_valid() const = 0;
    
    virtual GLuint get_handle() const = 0;                                                   // TODO: create abstract opengl object
    
    virtual std::string get_name() const = 0;
    
    virtual ~ITexture() {}
};

#endif /* ITexture_hpp */
