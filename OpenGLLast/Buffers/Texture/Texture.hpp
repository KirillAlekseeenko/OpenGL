//
//  Texture.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.04.2021.
//

#ifndef Texture_hpp
#define Texture_hpp

#include "ITexture.hpp"
#include "TextureInfo.hpp"

#include <iostream>

#include "Path.hpp"

class Texture : public ITexture
{
public:
    Texture();
    ~Texture();
    
    Texture(std::string path);
    
    Texture(const Texture& t) = delete;
    Texture& operator=(const Texture& t) = delete;
    
    Texture(Texture&& t);
    Texture& operator=(Texture&& t);
    
    void load_to_vram(GLenum type = GL_UNSIGNED_BYTE) override;
    
    void set_wrap_s(GLint type) override;
    void set_wrap_t(GLint type) override;
    void set_wrap_r(GLint type) override {}
    
    void set_min_filter(GLint type) override;
    void set_mag_filter(GLint type) override;
    
    bool is_valid() const override {return texture_info.is_valid();}
    
    GLuint get_handle() const override { return handle; }                                 // TODO: create abstract opengl object
    
    std::string get_name() const override;
    
    static std::unique_ptr<ITexture> create_texture(Dir dir, std::string path, GLenum type = GL_UNSIGNED_BYTE);
private:
    
    GLuint handle = 0;
    GLenum target = 0;                                                          // TODO: allow have any valid (not only GL_TEXTURE_2D) target
    
    TextureInfo texture_info;
    
    std::string path;
    
private:
    
    void binded(std::function<void(void)> action)
    {
        glBindTexture(GL_TEXTURE_2D, handle);
        
        action();
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    
    
    
};

#endif /* Texture_hpp */
