//
//  SpotLight.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.05.2021.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include "ILightSource.hpp"
#include <glm/glm.hpp>

class SpotLight : public ILightSource
{
public:
    std::shared_ptr<IDebugObject> get_visual_source() const override;                                     // lamp sun or another object acting as a sour
    std::unique_ptr<IShaderLightHalper> get_shader_helper() const override;
    
    LightType get_type() const override;
    
    SpotLight(glm::vec3 dir, glm::vec3 pos);
    
    glm::vec3 get_pos() const;
    glm::vec3 get_dir() const;
    float get_cut_off() const;
    float get_outer_cut_off() const;
    float get_constant() const;
    float get_linear() const;
    float get_quadratic() const;
    
    SpotLight& set_pos(glm::vec3 p);
    SpotLight& set_dir(glm::vec3 d);
    SpotLight& set_cut_off(float co);
    SpotLight& set_outer_cut_off(float oco);
    SpotLight& set_constant(float c);
    SpotLight& set_linear(float l);
    SpotLight& set_quadratic(float q);
    
    
private:
    glm::vec3 pos;
    glm::vec3 dir;
    
    float cut_off;
    float outer_cut_off;
    
    float constant;
    float linear;
    float quadratic;
};

#endif /* SpotLight_hpp */
