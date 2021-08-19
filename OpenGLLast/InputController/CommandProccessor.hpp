//
//  CommandProccessor.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 15.05.2021.
//

#ifndef CommandProccessor_hpp
#define CommandProccessor_hpp

#include "InputController.hpp"
#include "Actor.hpp"

class CommandProcessor
{
public:
    static bool ApplyCommand(std::pair<bool, std::unique_ptr<ICommand>> commandData, std::shared_ptr<IActor> actor);
};

#endif /* CommandProccessor_hpp */
