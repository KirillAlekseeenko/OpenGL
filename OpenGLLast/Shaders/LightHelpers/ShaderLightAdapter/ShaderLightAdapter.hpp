//
//  ShaderLightAdapter.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 20.06.2021.
//

#ifndef ShaderLightAdapter_hpp
#define ShaderLightAdapter_hpp

#include "IShaderLightAdapter.hpp"
#include "ShaderProgram.hpp"

class ShaderLightAdapter : public IShaderLightAdapter
{
public:
    
    ShaderLightAdapter(ShaderProgram* s);
    
    ShaderLightAdapter(const ShaderLightAdapter& sla) = delete;
    ShaderLightAdapter& operator=(const ShaderLightAdapter& sla) = delete;
    
    ShaderLightAdapter(ShaderLightAdapter&& sla) = delete;
    ShaderLightAdapter& operator=(ShaderLightAdapter&& sla) = delete;
    
    void set_dir_light(const DirectionalLight* dir_light) override;
    void set_spot_light(const SpotLight* spot_light) override;
    void set_point_light(const PointLight* point_light) override;
private:
    ShaderProgram* shader;
};

#endif /* ShaderLightAdapter_hpp */
