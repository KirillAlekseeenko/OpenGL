//
//  Texture.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.04.2021.
//

#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture() : target {GL_TEXTURE_2D}                  // for simplicity default texture_2d
{
    glGenTextures(1, &handle);
}

Texture::~Texture()
{
    if (handle != 0)
    {
        glDeleteTextures(1, &handle);
    }
}

Texture::Texture(std::string p) : Texture()
{
    this->path = p;
    
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    
    auto data = static_cast<unsigned char*>(stbi_load(path.c_str(), &width, &height, &nrChannels, 0));
    
    texture_info = TextureInfo(data, width, height, nrChannels);
}

Texture::Texture(Texture&& t) : handle{t.handle}, texture_info {std::move(t.texture_info)}
{
    t.handle = 0;
}

Texture& Texture::operator=(Texture&& t)
{
    if (handle != t.handle)
    {
        this->~Texture();
    }
    
    texture_info = std::move(t.texture_info);
    handle = t.handle;
    
    t.handle = 0;
    
    return *this;
}

void Texture::load_to_vram(GLenum type)
{
    if (!is_valid()) return;
    
    binded([this, type] ()
    {
        GLenum format = GL_RED;
        
        switch(texture_info.get_channels_count())
        {
            case 1: format = GL_RED; break;
            case 3: format = GL_RGB; break;
            case 4: format = GL_RGBA; break;
        }
        
        auto data = texture_info.get_data();
        
        glTexImage2D(GL_TEXTURE_2D, 0, format, texture_info.get_width(), texture_info.get_height(), 0, format, type, data);
        
        if (data != nullptr) glGenerateMipmap(GL_TEXTURE_2D);
    });
}

void Texture::set_wrap_s(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
    });
}

void Texture::set_wrap_t(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
    });
}

void Texture::set_min_filter(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
    });
}

void Texture::set_mag_filter(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
    });
}

std::string Texture::get_name() const
{
    return path;
}

std::unique_ptr<ITexture> Texture::create_texture(Dir dir, std::string path, GLenum type)
{
    return std::make_unique<Texture>(dir.get_relative_path(path));
}
