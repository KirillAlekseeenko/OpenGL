//
//  DirLightActor.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.06.2021.
//

#include "DirLightActor.hpp"

DirLightActor::DirLightActor(std::shared_ptr<DirectionalLight> d) : dir_light{d}
{
    auto direction = d->get_direction();
    
    current_pitch = glm::asin(direction.y);
    
    current_pitch = std::clamp(current_pitch, -pitch_constrain, pitch_constrain);
    
    current_yaw = glm::atan(direction.x, direction.z);
}

void DirLightActor::move_offset(glm::vec3 offset)
{
    
}

void DirLightActor::rotate_offset(glm::vec3 offset)
{
    auto pitch = offset.x;
    auto yaw = -offset.y;
    
    current_pitch += pitch;
    current_yaw += yaw;
    
    current_pitch = std::clamp(current_pitch, -pitch_constrain, pitch_constrain);
    
    auto direction = glm::vec3(0.0f);
    
    direction.z = cos(current_yaw);
    direction.x = sin(current_yaw);
    
    direction.x = direction.x * cos(current_pitch);
    direction.z = direction.z * cos(current_pitch);
    
    direction.y = sin(current_pitch);
    
    direction = glm::normalize(direction);
    
    dir_light->set_direction(direction);
}
