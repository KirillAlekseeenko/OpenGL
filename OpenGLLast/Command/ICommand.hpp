//
//  ICommand.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.04.2021.
//

#ifndef ICommand_h
#define ICommand_h

#include <iostream>
#include "Actor.hpp"

class ICommand
{
public:
    virtual void execute(std::shared_ptr<IActor> actor) = 0;
    virtual ~ICommand() {}
};

#endif /* ICommand_h */
