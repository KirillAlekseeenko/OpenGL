//
//  Actor.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.04.2021.
//

#ifndef Actor_h
#define Actor_h

#include <iostream>

#include <glm/glm.hpp>

class IActor
{
public:
    virtual void move_offset(glm::vec3 offset) = 0;
    virtual void rotate_offset(glm::vec3 offset) = 0;             // euler angles (pitch, yaw, roll)
};

#endif /* Actor_h */
