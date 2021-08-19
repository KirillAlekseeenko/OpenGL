//
//  ShaderLightAdapter.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 19.06.2021.
//

#ifndef ShaderLightArrayAdapter_hpp
#define ShaderLightArrayAdapter_hpp

#include "ShaderProgram.hpp"

#include "IShaderLightAdapter.hpp"

// TODO: create light array adapter and without array as a strategy pattern

class ShaderLightArrayAdapter : public IShaderLightAdapter
{
public:
    ShaderLightArrayAdapter(ShaderProgram* s);
    
    ShaderLightArrayAdapter(const ShaderLightArrayAdapter& sla) = delete;
    ShaderLightArrayAdapter& operator=(const ShaderLightArrayAdapter& sla) = delete;
    
    ShaderLightArrayAdapter(ShaderLightArrayAdapter&& sla) = delete;
    ShaderLightArrayAdapter& operator=(ShaderLightArrayAdapter&& sla) = delete;
    
    void set_dir_light(const DirectionalLight* dir_light) override;
    void set_spot_light(const SpotLight* spot_light) override;
    void set_point_light(const PointLight* point_light) override;
private:
    ShaderProgram* shader;
    
    int dir_lights_set_count = 0;
    int point_lights_set_count = 0;
    int spot_lights_set_count = 0;
};

#endif /* ShaderLightArrayAdapter_hpp */
