//
//  PointLightActor.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.06.2021.
//

#include "PointLightActor.hpp"

PointLightActor::PointLightActor(std::shared_ptr<PointLight> p) : point_light{p}
{
}

void PointLightActor::move_offset(glm::vec3 offset)
{
    point_light->translate(offset);
}

void PointLightActor::rotate_offset(glm::vec3 offset)
{
}
