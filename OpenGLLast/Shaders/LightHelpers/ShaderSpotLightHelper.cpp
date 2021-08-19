//
//  ShaderSpotLightHelper.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 06.06.2021.
//

#include "ShaderSpotLightHelper.hpp"

void ShaderSpotLightHelper::apply(IShaderLightAdapter *s)
{
    s->set_spot_light(spot_light);
}
