//
//  CommandProccessor.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 15.05.2021.
//

#include "CommandProccessor.hpp"


bool CommandProcessor::ApplyCommand(std::pair<bool, std::unique_ptr<ICommand>> commandData, std::shared_ptr<IActor> actor)
{
    if (!commandData.first) return false;
    
    commandData.second->execute(actor);
    
    return true;
}
