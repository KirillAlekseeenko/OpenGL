//
//  PointLight.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.05.2021.
//

#ifndef PointLight_hpp
#define PointLight_hpp

#include "ILightSource.hpp"
#include "PointLightCube.hpp"

class PointLight : public ILightSource
{
public:
    
    PointLight(glm::vec3 pos);
    
    std::shared_ptr<IDebugObject> get_visual_source() const override;                                     // lamp sun or another object acting as a sour
    std::unique_ptr<IShaderLightHalper> get_shader_helper() const override;
    
    LightType get_type() const override;
    
    glm::vec3 get_pos() const;
    float get_constant() const;
    float get_linear() const;
    float get_quadratic() const;
    
    PointLight& set_pos(glm::vec3 p);
    PointLight& set_constant(float c);
    PointLight& set_linear(float l);
    PointLight& set_quadratic(float q);
    
    PointLight& translate(glm::vec3 t);
    
    static std::shared_ptr<PointLight> create_point_light(glm::vec3 pos, float c, float l, float q);
    
private:
    
    void update_visual_repr();
    
private:
    
    glm::vec3 pos;
    
    float constant = 1.0f;
    float linear = 0.35f;
    float quadratic = 0.44f;
    
    std::shared_ptr<PointLightCube> visual_repr;
};

#endif /* PointLight_hpp */
