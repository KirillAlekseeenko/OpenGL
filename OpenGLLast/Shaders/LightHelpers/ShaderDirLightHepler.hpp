//
//  ShaderDirLightHepler.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 06.06.2021.
//

#ifndef ShaderDirLightHepler_hpp
#define ShaderDirLightHepler_hpp

#include "IShaderLightHelper.hpp"
#include "DirectionalLight.hpp"

class ShaderDirLightHelper : public IShaderLightHalper
{
public:
    ShaderDirLightHelper(const DirectionalLight *d);
    
    void apply(IShaderLightAdapter *s) override;
private:
    const DirectionalLight *dir_light;
};

#endif /* ShaderDirLightHepler_hpp */
