//
//  DirectionalLight.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.05.2021.
//

#include "DirectionalLight.hpp"

#include "ShaderDirLightHepler.hpp"

DirectionalLight::DirectionalLight(glm::vec3 d) : direction{d}, visual_pos {0.0f, 2.0f, 0.0f}
{
    check_dir(d);
    
    visual_repr = std::make_shared<Vector>();
    
    update_visual_obj();
}

std::shared_ptr<IDebugObject> DirectionalLight::get_visual_source() const
{
    return visual_repr;
}

std::unique_ptr<IShaderLightHalper> DirectionalLight::get_shader_helper() const
{
    return std::make_unique<ShaderDirLightHelper>(this);
}

LightType DirectionalLight::get_type() const
{
    return LightType::Directional;
}

void DirectionalLight::set_direction(glm::vec3 d)
{
    check_dir(d);
    
    direction = d;
    
    update_visual_obj();
}

glm::vec3 DirectionalLight::get_direction() const
{
    return direction;
}

void DirectionalLight::set_visual_pos(glm::vec3 d)
{
    visual_pos = d;
    
    update_visual_obj();
}

glm::vec3 DirectionalLight::get_visual_pos() const
{
    return visual_pos;
}


void DirectionalLight::check_dir(glm::vec3 d)
{
    if (d.length() == 0) throw std::runtime_error("invalid dir");
}

void DirectionalLight::update_visual_obj()
{
    visual_repr->set_positon(visual_pos, direction);
}

