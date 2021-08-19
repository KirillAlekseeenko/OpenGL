//
//  IShaderLightAdapter.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 20.06.2021.
//

#include "IShaderLightAdapter.hpp"

const std::string IShaderLightAdapter::dir_light_dir_uniform_name = "dirLightDir";
const std::string IShaderLightAdapter::point_light_pos_uniform_name = "pointLightPos";
const std::string IShaderLightAdapter::spot_light_dir_uniform_name = "spotLightDir";
const std::string IShaderLightAdapter::spot_light_pos_uniform_name = "spotLightPos";

const std::string IShaderLightAdapter::point_light_data_uniform_name = "pointLights";
const std::string IShaderLightAdapter::spot_light_data_uniform_name = "spotLights";

const std::string IShaderLightAdapter::constant_field_name = "constant";
const std::string IShaderLightAdapter::linear_field_name = "linear";
const std::string IShaderLightAdapter::quadratic_field_name = "quadratic";

const std::string IShaderLightAdapter::cut_off_field_name = "cutOff";
const std::string IShaderLightAdapter::outer_cut_off_field_name = "outerCutOff";
