//
//  IDObj.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 24.04.2021.
//

#include "IDObj.hpp"

int IDObj::current_id = 0;

int IDObj::get_id() const
{
    return id;
}

IDObj::IDObj()
{
    id = current_id;                          // TODO: not thread safe
    current_id++;
}
