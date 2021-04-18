//
//  Move.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#ifndef Move_hpp
#define Move_hpp

#include "ICommand.hpp"
#include <glm/glm.hpp>

class Move : public ICommand
{
public:
    Move(glm::vec3 m);
    
    void execute(std::shared_ptr<IActor> actor) override;
private:
    glm::vec3 movement;
};

#endif /* Move_hpp */
