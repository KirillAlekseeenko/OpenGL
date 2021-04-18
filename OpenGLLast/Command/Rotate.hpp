//
//  Rotate.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#ifndef Rotate_hpp
#define Rotate_hpp

#include "ICommand.hpp"
#include <glm/glm.hpp>

class Rotate : public ICommand
{
public:
    Rotate(glm::vec3 r);
    void execute(std::shared_ptr<IActor> actor) override;
private:
    glm::vec3 rotation;
};

#endif /* Rotate_hpp */
