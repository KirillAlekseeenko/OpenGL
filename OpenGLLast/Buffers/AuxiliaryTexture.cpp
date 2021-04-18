//
//  AuxiliaryTexture.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#include "AuxiliaryTexture.hpp"

AuxiliaryTexture::AuxiliaryTexture(std::shared_ptr<Texture> t, int begin, int count) : texture{t}, begin_vertex_index{begin}, vertex_count{count}
{
}
