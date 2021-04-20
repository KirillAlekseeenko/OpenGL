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
    
    if (data != nullptr)
    {
        stbi_image_free(data);
    }
}

Texture::Texture(std::string p) : Texture()
{
    set_texture_data(p);
}

Texture::Texture(Texture&& t) : data{t.data}, handle{t.handle}, width{t.width}, height{t.height}, nrChannels{t.nrChannels}
{
    t.data = nullptr;
    t.handle = 0;
    t.width = 0;
    t.height = 0;
    t.nrChannels = 0;
}

Texture& Texture::operator=(Texture&& t)
{
    if (handle != t.handle)
    {
        this->~Texture();
    }
    
    data = t.data;
    width = t.width;
    height = t.height;
    handle = t.handle;
    nrChannels = t.nrChannels;
    
    return *this;
}

Texture& Texture::set_texture_data(std::string path)
{
    this->path = path;
    
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    
    if (data)
    {
        binded([this] ()
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        });
    }
    
    return *this;
}

Texture& Texture::set_wrap_s(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, type);
    });
    
    return *this;
}

Texture& Texture::set_wrap_t(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, type);
    });
    
    return *this;
}

Texture& Texture::set_min_filter(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, type);
    });
    
    return *this;
}

Texture& Texture::set_mag_filter(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, type);
    });
    
    return *this;
}

std::string Texture::get_path() const
{
    return path;
}
