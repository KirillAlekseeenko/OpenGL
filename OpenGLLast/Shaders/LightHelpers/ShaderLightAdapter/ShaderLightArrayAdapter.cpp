//
//  ShaderLightAdapter.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 19.06.2021.
//

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

#include "Meta.hpp"

#include "ShaderLightArrayAdapter.hpp"

ShaderLightArrayAdapter::ShaderLightArrayAdapter(ShaderProgram* s) : shader{s}
{
}

void ShaderLightArrayAdapter::set_dir_light(const DirectionalLight *dir_light)
{
    shader->set_vec3(construct(dir_light_dir_uniform_name, '[', dir_lights_set_count, ']'), dir_light->get_direction());
    
    dir_lights_set_count++;
}

void ShaderLightArrayAdapter::set_point_light(const PointLight *point_light)
{
    auto i = point_lights_set_count;
    
    shader->set_vec3(construct(point_light_pos_uniform_name, '[', i, ']'), point_light->get_pos());
    
    shader->set_float(construct(point_light_data_uniform_name, '[', i, ']', '.', constant_field_name), point_light->get_constant());
    shader->set_float(construct(point_light_data_uniform_name, '[', i, ']', '.', quadratic_field_name), point_light->get_quadratic());
    shader->set_float(construct(point_light_data_uniform_name, '[', i, ']', '.', linear_field_name), point_light->get_linear());
    
    point_lights_set_count++;
}

void ShaderLightArrayAdapter::set_spot_light(const SpotLight *spot_light)
{
    auto i = spot_lights_set_count;
    
    shader->set_vec3(construct(spot_light_pos_uniform_name, '[', i, ']'), spot_light->get_pos());
    shader->set_vec3(construct(spot_light_dir_uniform_name, '[', i, ']'), spot_light->get_dir());
    
    shader->set_float(construct(spot_light_data_uniform_name, '[', i, ']', '.', constant_field_name), spot_light->get_constant());
    shader->set_float(construct(spot_light_data_uniform_name, '[', i, ']', '.', linear_field_name), spot_light->get_linear());
    shader->set_float(construct(spot_light_data_uniform_name, '[', i, ']', '.', quadratic_field_name), spot_light->get_quadratic());
    
    shader->set_float(construct(spot_light_data_uniform_name, '[', i, ']', '.', cut_off_field_name), spot_light->get_cut_off());
    shader->set_float(construct(spot_light_data_uniform_name, '[', i, ']', '.', outer_cut_off_field_name), spot_light->get_outer_cut_off());
    
    spot_lights_set_count++;
}

