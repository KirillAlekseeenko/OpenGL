//
//  SpotLight.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.05.2021.
//

#include "SpotLight.hpp"

SpotLight::SpotLight(glm::vec3 d, glm::vec3 p) : dir {d}, pos{p}
{
}


glm::vec3 SpotLight::get_pos() const
{
    return pos;
}

glm::vec3 SpotLight::get_dir() const
{
    return dir;
}

float SpotLight::get_cut_off() const
{
    return cut_off;
}

float SpotLight::get_outer_cut_off() const
{
    return outer_cut_off;
}

float SpotLight::get_constant() const
{
    return constant;
}

float SpotLight::get_linear() const
{
    return linear;
}

float SpotLight::get_quadratic() const
{
    return quadratic;
}

SpotLight& SpotLight::set_pos(glm::vec3 p)
{
    pos = p;
    
    return *this;
}

SpotLight& SpotLight::set_dir(glm::vec3 d)
{
    dir = d;
    
    return *this;
}

SpotLight& SpotLight::set_cut_off(float co)
{
    cut_off = co;
    
    return *this;
}

SpotLight& SpotLight::set_outer_cut_off(float oco)
{
    outer_cut_off = oco;
    
    return *this;
}

SpotLight& SpotLight::set_constant(float c)
{
    constant = c;
    
    return *this;
}

SpotLight& SpotLight::set_linear(float l)
{
    linear = l;
    
    return *this;
}

SpotLight& SpotLight::set_quadratic(float q)
{
    quadratic = q;
    
    return *this;
}

std::shared_ptr<IDebugObject> SpotLight::get_visual_source() const
{
    throw std::runtime_error{"not implemented"};
}

std::unique_ptr<IShaderLightHalper> SpotLight::get_shader_helper() const
{
    throw std::runtime_error{"not implemented"};
}

LightType SpotLight::get_type() const
{
    return LightType::Spot;
}
