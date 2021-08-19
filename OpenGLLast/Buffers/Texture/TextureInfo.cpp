//
//  TextureInfo.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 29.05.2021.
//

#include "TextureInfo.hpp"
#include <stb/stb_image.h>

TextureInfo::~TextureInfo()
{
    if (is_valid())
    {
        stbi_image_free(data);
    }
}

TextureInfo::TextureInfo(unsigned char* d, int w, int h, int chnls) : data{d}, width{w}, height{h}, nrChannels{chnls}
{
}

TextureInfo& TextureInfo::operator=(TextureInfo &&ti)
{
    this->~TextureInfo();
    
    data = ti.data;                                                          // TODO: try swap(this, &ti);
    width = ti.width;
    height = ti.height;
    nrChannels = ti.nrChannels;
    
    ti.set_to_default();
    
    return *this;
}

TextureInfo::TextureInfo(TextureInfo &&ti) : data{ti.data}, width{ti.width}, height{ti.height}, nrChannels{ti.nrChannels}
{
    ti.set_to_default();
}
