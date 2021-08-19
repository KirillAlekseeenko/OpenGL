//
//  ShaderLightAdapter.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 20.06.2021.
//

#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "SpotLight.hpp"

#include "ShaderLightAdapter.hpp"

#include "Meta.hpp"

ShaderLightAdapter::ShaderLightAdapter(ShaderProgram* s) : shader{s}
{
}

void ShaderLightAdapter::set_dir_light(const DirectionalLight *dir_light)
{
    shader->set_vec3(dir_light_dir_uniform_name, dir_light->get_direction());
}

void ShaderLightAdapter::set_point_light(const PointLight *point_light)
{
    shader->set_vec3(point_light_pos_uniform_name, point_light->get_pos());
    
    shader->set_float(construct(point_light_data_uniform_name, '.', constant_field_name), point_light->get_constant());
    shader->set_float(construct(point_light_data_uniform_name, '.', quadratic_field_name), point_light->get_quadratic());
    shader->set_float(construct(point_light_data_uniform_name, '.', linear_field_name), point_light->get_linear());
}

void ShaderLightAdapter::set_spot_light(const SpotLight *spot_light)
{
    shader->set_vec3(construct(spot_light_pos_uniform_name), spot_light->get_pos());
    shader->set_vec3(construct(spot_light_dir_uniform_name), spot_light->get_dir());
    
    shader->set_float(construct(spot_light_data_uniform_name, '.', constant_field_name), spot_light->get_constant());
    shader->set_float(construct(spot_light_data_uniform_name, '.', linear_field_name), spot_light->get_linear());
    shader->set_float(construct(spot_light_data_uniform_name, '.', quadratic_field_name), spot_light->get_quadratic());
    
    shader->set_float(construct(spot_light_data_uniform_name, '.', cut_off_field_name), spot_light->get_cut_off());
    shader->set_float(construct(spot_light_data_uniform_name, '.', outer_cut_off_field_name), spot_light->get_outer_cut_off());
}
