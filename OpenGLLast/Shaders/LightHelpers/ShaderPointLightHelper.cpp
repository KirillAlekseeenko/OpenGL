//
//  ShaderPointLightHelper.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 06.06.2021.
//

#include "ShaderPointLightHelper.hpp"

ShaderPointLightHelper::ShaderPointLightHelper(const PointLight* p) : point_light{p}
{
}

void ShaderPointLightHelper::apply(IShaderLightAdapter *s)
{
    s->set_point_light(point_light);
}
