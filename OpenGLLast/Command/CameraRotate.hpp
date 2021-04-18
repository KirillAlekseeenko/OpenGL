//
//  CameraRotate.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#ifndef CameraRotate_hpp
#define CameraRotate_hpp

#include "ICommand.hpp"

class CameraRotate : public ICommand
{
public:
    void execute(std::shared_ptr<IActor> actor) override;
};

#endif /* CameraRotate_hpp */
