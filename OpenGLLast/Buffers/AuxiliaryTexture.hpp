//
//  AuxiliaryTexture.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#ifndef AuxiliaryTexture_hpp
#define AuxiliaryTexture_hpp

#include "Texture.hpp"

class AuxiliaryTexture
{
public:
    AuxiliaryTexture(std::shared_ptr<Texture> t, int begin, int count);
    
    std::pair<int, int> get_begin_end_interval() { return std::make_pair(begin_vertex_index, begin_vertex_index + vertex_count); }
    std::shared_ptr<Texture> get_texture() {return texture;}
private:
    std::shared_ptr<Texture> texture;
    int begin_vertex_index;
    int vertex_count;
};

#endif /* AuxiliaryTexture_hpp */
