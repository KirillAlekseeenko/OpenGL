//
//  IShaderLightAdapter.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 20.06.2021.
//

#ifndef IShaderLightAdapter_hpp
#define IShaderLightAdapter_hpp

class DirectionalLight;
class SpotLight;
class PointLight;

#include "string"

class IShaderLightAdapter                       // TODO: perhaps should make it more common for array/usual uniform types
{
protected:
    static const std::string dir_light_dir_uniform_name;
    static const std::string point_light_pos_uniform_name;
    static const std::string spot_light_dir_uniform_name;
    static const std::string spot_light_pos_uniform_name;
    
    static const std::string point_light_data_uniform_name;
    static const std::string spot_light_data_uniform_name;
    
    static const std::string constant_field_name;
    static const std::string linear_field_name;
    static const std::string quadratic_field_name;
    static const std::string cut_off_field_name;
    static const std::string outer_cut_off_field_name;
    
    // TODO: think of more robust systems for constructing shader uniform name
    
public:
    virtual void set_dir_light(const DirectionalLight* dir_light) = 0;
    virtual void set_spot_light(const SpotLight* spot_light) = 0;
    virtual void set_point_light(const PointLight* point_light) = 0;
    virtual ~IShaderLightAdapter() {}
};

#endif /* IShaderLightAdapter_hpp */
