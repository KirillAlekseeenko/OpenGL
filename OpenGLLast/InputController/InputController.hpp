//
//  InputController.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#ifndef InputController_hpp
#define InputController_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ICommand.hpp"

class InputController
{
public:
    std::pair<bool, std::unique_ptr<ICommand>> try_get_movement_cmd(GLFWwindow* window, float delta);
    std::pair<bool, std::unique_ptr<ICommand>> try_get_view_cmd(GLFWwindow* window, float delta);
    std::pair<bool, std::unique_ptr<ICommand>> try_process_secondary_movement(GLFWwindow* window, float delta, float sense);
    std::pair<bool, std::unique_ptr<ICommand>> try_process_secondary_rotation(GLFWwindow* window, float delta, float sense = 1.0f);
    
    
    InputController& set_movement_sense(float s);
    InputController& set_view_sense(float s);
private:
    float movement_sense = 1.0f;
    float view_sense = 1.0f;
};

#endif /* InputController_hpp */
