//
//  PointLight.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.05.2021.
//

#include "PointLight.hpp"

#include "ShaderPointLightHelper.hpp"

PointLight::PointLight(glm::vec3 p) : pos{p}
{
    visual_repr = std::make_shared<PointLightCube>(0.2f);
    
    update_visual_repr();
}

glm::vec3 PointLight::get_pos() const
{
    return pos;
}

float PointLight::get_constant() const
{
    return constant;
}

float PointLight::get_linear() const
{
    return linear;
}

float PointLight::get_quadratic() const
{
    return quadratic;
}

PointLight& PointLight::set_pos(glm::vec3 p)
{
    pos = p;
    
    update_visual_repr();
    
    return *this;
}

PointLight& PointLight::set_constant(float c)
{
    constant = c;
    
    return *this;
}

PointLight& PointLight::set_linear(float l)
{
    linear = l;
    
    return *this;
}

PointLight& PointLight::set_quadratic(float q)
{
    quadratic = q;
    
    return *this;
}

PointLight& PointLight::translate(glm::vec3 t)
{
    set_pos(pos += t);
    
    update_visual_repr();
    
    return *this;
}

std::shared_ptr<IDebugObject> PointLight::get_visual_source() const
{
    return visual_repr;
}

std::unique_ptr<IShaderLightHalper> PointLight::get_shader_helper() const
{
    return std::make_unique<ShaderPointLightHelper>(this);
}

LightType PointLight::get_type() const
{
    return LightType::Point;
}

void PointLight::update_visual_repr()
{
    visual_repr->set_position(pos);
}

std::shared_ptr<PointLight> PointLight::create_point_light(glm::vec3 pos, float c, float l, float q)
{
    auto pl = std::make_shared<PointLight>(pos);
    
    pl->set_linear(l)
    .set_constant(c)
    .set_quadratic(q);
    
    return pl;
}
