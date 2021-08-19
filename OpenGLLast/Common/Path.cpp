//
//  Path.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 15.05.2021.
//

#include "Path.hpp"


Dir::Dir(std::string p) : path{p}
{
}

std::string Dir::get_relative_path(std::string p)
{
    return path + p;
}
