//
//  Move.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#include "Move.hpp"

Move::Move(glm::vec3 m) : movement{m}
{
}

void Move::execute(std::shared_ptr<IActor> actor)
{
    actor->move_offset(movement);
}
