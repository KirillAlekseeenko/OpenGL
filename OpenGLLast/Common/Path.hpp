//
//  Path.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 15.05.2021.
//

#ifndef Path_hpp
#define Path_hpp

#include <string>

class Dir
{
public:
    Dir(std::string p);
    std::string get_relative_path(std::string);
private:
    std::string path;
};

#endif /* Path_hpp */
