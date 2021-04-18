//
//  Rotate.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#include "Rotate.hpp"

Rotate::Rotate(glm::vec3 r) : rotation{r}
{
    
}

void Rotate::execute(std::shared_ptr<IActor> actor)
{
    actor->rotate_offset(rotation);
}
