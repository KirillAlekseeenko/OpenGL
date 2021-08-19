//
//  ILightSource.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.05.2021.
//

#ifndef ILightSource_hpp
#define ILightSource_hpp

#include <iostream>
#include "IShaderLightHelper.hpp"
#include "IDebugObject.hpp"
#include "LightType.hpp"

class ShaderProgram;

class ILightSource
{
public:
    virtual std::shared_ptr<IDebugObject> get_visual_source() const = 0;                                     // lamp sun or another object acting as a source
    virtual std::unique_ptr<IShaderLightHalper> get_shader_helper() const = 0;
    
    virtual LightType get_type() const = 0;
    
    //virtual std::shared_ptr<ShaderProgram> get_shadow_mapping_shader() const = 0;
    //virtual glm::vec3 get_shadow_mapping_pos() const = 0;
};

#endif /* ILightSource_hpp */
