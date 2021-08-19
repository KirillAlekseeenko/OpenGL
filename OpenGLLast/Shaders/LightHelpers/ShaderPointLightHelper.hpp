//
//  ShaderPointLightHelper.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 06.06.2021.
//

#ifndef ShaderPointLightHelper_hpp
#define ShaderPointLightHelper_hpp

#include "IShaderLightHelper.hpp"
#include "PointLight.hpp"

class ShaderPointLightHelper : public IShaderLightHalper
{
public:
    ShaderPointLightHelper(const PointLight* point_light);
    
    void apply(IShaderLightAdapter *s) override;
private:
    const PointLight *point_light;
};

#endif /* ShaderPointLightHelper_hpp */
