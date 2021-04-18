//
//  Camera.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 15.04.2021.
//

#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <algorithm>

/* camera looks along z axis */

Camera::Camera()
{
}

glm::vec3 Camera::get_position()
{
    return position;
}

glm::vec3 Camera::get_look_pos()
{
    return position + direction;
}

glm::vec3 Camera::get_up_vector()
{
    return glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::get_look_at()
{
    return glm::lookAt(position, get_look_pos(), get_up_vector());
}

Camera& Camera::set_postion(glm::vec3 pos)
{
    position = pos;
    
    return *this;
}

void Camera::move_offset(glm::vec3 offset)
{
    auto forward = offset.z;
    auto left = -offset.x;
    
    auto leftDir = glm::cross(direction, get_up_vector());
    
    position = position + forward * direction;
    position = position + left * leftDir;
}

void Camera::rotate_offset(glm::vec3 offset)
{
    auto pitch = offset.x;
    auto yaw = -offset.y;
    
    current_pitch += pitch;
    current_yaw += yaw;
    
    current_pitch = std::clamp(current_pitch, -pitch_constrain, pitch_constrain);
    
    direction.z = cos(current_yaw);
    direction.x = sin(current_yaw);
    
    direction.x = direction.x * cos(current_pitch);
    direction.z = direction.z * cos(current_pitch);
    
    direction.y = sin(current_pitch);
    
    direction = glm::normalize(direction);
}
