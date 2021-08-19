//
//  ShadowMappingSpecification.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 01.07.2021.
//

#ifndef ShadowMappingSpecification_hpp
#define ShadowMappingSpecification_hpp

#include "ShaderProgram.hpp"

class ShadowMappingSpecification
{
public:
    std::shared_ptr<ShaderProgram> get_shadow_mapping_shader();
    
};

#endif /* ShadowMappingSpecification_hpp */
