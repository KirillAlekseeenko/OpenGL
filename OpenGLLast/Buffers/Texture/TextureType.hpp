//
//  TextureType.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 22.05.2021.
//

#ifndef TextureType_h
#define TextureType_h

enum class TextureType : std::size_t {Diffuse = 0, Normal = 1, Specular = 2, Displacement = 3, Cubemap = 4};

const std::size_t maps_types_count = 5;

#endif /* TextureType_h */
