//
//  Cubemap.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 26.05.2021.
//

#include "Cubemap.hpp"
#include <iostream>

#include <sstream>

#include <stb/stb_image.h>

Cubemap::~Cubemap()
{
    if (handle != 0)
    {
        glDeleteTextures(1, &handle);
    }
}

// TODO: incapsulate texture data from stbi_load in some class
Cubemap::Cubemap(std::array<std::string, CUBEMAP_SIDES_COUNT> map_paths)
{
    glGenTextures(1, &handle);
    
    std::stringstream ss;
    ss << "cubemap_" << handle;
    
    name = ss.str();
    
    for (auto i = 0; i < CUBEMAP_SIDES_COUNT; i++)
    {
        int width = 0;
        int height = 0;
        int nrChannels = 0;
        
        auto data = static_cast<unsigned char*>(stbi_load(map_paths[i].c_str(), &width, &height, &nrChannels, 0));
        
        textures_info[i] = TextureInfo(data, width, height, nrChannels);
    }
}

void Cubemap::load_to_vram(GLenum type)
{
    if (!is_valid()) return;
    
    binded([this, type]
    {
        for (auto i = 0; i < CUBEMAP_SIDES_COUNT; i++)
        {
            auto& ti = textures_info[i];
            
            auto format = GL_RGB;
            
            switch(ti.get_channels_count())
            {
                case 1: format = GL_RED; break;
                case 4: format = GL_RGBA; break;
            }
            
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, ti.get_width(), ti.get_height(), 0, format, type, ti.get_data());
            
            //glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        }
    });
    
    /*
     When not setting the min filter it won't just magically not work.
     Instead the default of GL_NEAREST_MIPMAP_LINEAR is used and since you DON'T specify texture images for the other mipmap layers, it won't work
     So you either generate mipmaps or set min filter linear or nearest
     */
    
    set_wrap_r(GL_CLAMP_TO_EDGE);
    set_wrap_s(GL_CLAMP_TO_EDGE);
    set_wrap_t(GL_CLAMP_TO_EDGE);
    set_mag_filter(GL_LINEAR);
    set_min_filter(GL_LINEAR);
}

Cubemap::Cubemap(Cubemap&& t) : textures_info(std::move(t.textures_info)), handle(t.handle), target(t.target), name {t.name}
{
    t.handle = 0;
}

Cubemap& Cubemap::operator=(Cubemap&& t)
{
    if (handle != t.handle)
    {
        this->~Cubemap();
    }
    
    handle = t.handle;
    textures_info = std::move(t.textures_info);
    target = t.target;
    name = t.name;
    
    t.handle = 0;
    
    return *this;
}

void Cubemap::set_wrap_s(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, type);
    });
}
void Cubemap::set_wrap_t(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, type);
    });
}

void Cubemap::set_wrap_r(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, type);
    });
}

void Cubemap::set_min_filter(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, type);
    });
}

void Cubemap::set_mag_filter(GLint type)
{
    binded([this, type] ()
    {
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, type);
    });
}

std::unique_ptr<ITexture> Cubemap::create_cubemap(Dir dir, std::array<std::string, CUBEMAP_SIDES_COUNT> map_paths, GLenum type)
{
    std::transform(map_paths.begin(), map_paths.end(), map_paths.begin(), [&dir](std::string local_path)
    {
        return dir.get_relative_path(std::move(local_path));
    });
    
    return std::make_unique<Cubemap>(std::move(map_paths));
}

std::string Cubemap::get_name() const
{
    return name;
}
