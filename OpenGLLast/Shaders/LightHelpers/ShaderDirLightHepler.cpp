//
//  ShaderDirLightHepler.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 06.06.2021.
//

#include "ShaderDirLightHepler.hpp"

ShaderDirLightHelper::ShaderDirLightHelper(const DirectionalLight* d) : dir_light{d}
{
}

void ShaderDirLightHelper::apply(IShaderLightAdapter *s)
{
    s->set_dir_light(dir_light);
}
