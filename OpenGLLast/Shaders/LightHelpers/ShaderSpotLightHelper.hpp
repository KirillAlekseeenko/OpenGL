//
//  ShaderSpotLightHelper.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 06.06.2021.
//

#ifndef ShaderSpotLightHelper_hpp
#define ShaderSpotLightHelper_hpp

#include "IShaderLightHelper.hpp"
#include "SpotLight.hpp"

class ShaderSpotLightHelper : public IShaderLightHalper
{
public:
    void apply(IShaderLightAdapter *s) override;
private:
    SpotLight* spot_light;
};

#endif /* ShaderSpotLightHelper_hpp */
