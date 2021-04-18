//
//  Camera.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 15.04.2021.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Actor.hpp"

class Camera : public IActor
{
public:
    Camera();
    
    glm::vec3 get_position();
    glm::vec3 get_look_pos();
    glm::vec3 get_up_vector();
    glm::mat4 get_look_at();
    
    Camera& set_postion(glm::vec3 pos);
    
    void move_offset(glm::vec3 offset) override;
    void rotate_offset(glm::vec3 offset) override;
    
private:
    glm::vec3 position{0.0f};
    glm::vec3 direction{0.0f, 0.0f, -1.0f};
    
    float current_pitch = 0;
    float current_yaw = (float) M_PI;
    
    static constexpr float pitch_constrain = (float) M_PI_2 - 0.05f;
};

#endif /* Camera_hpp */
