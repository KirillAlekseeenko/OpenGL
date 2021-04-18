//
//  InputController.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 17.04.2021.
//

#include "InputController.hpp"

#include "Move.hpp"
#include "Rotate.hpp"

InputController& InputController::set_view_sense(float s)
{
    view_sense = s;
    return *this;
}

InputController& InputController::set_movement_sense(float s)
{
    movement_sense = s;
    return *this;
}

std::pair<bool, std::unique_ptr<ICommand>> InputController::try_process_view(GLFWwindow* window, float delta)
{
    float cameraRotSpeed = view_sense * delta;
    glm::vec3 rotation{0.0f, 0.0f, 0.0f};
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            rotation.x += cameraRotSpeed;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            rotation.x -= cameraRotSpeed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            rotation.y += cameraRotSpeed;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            rotation.y -= cameraRotSpeed;
    
    if (rotation.x == 0 && rotation.y == 0) return std::make_pair(false, std::unique_ptr<ICommand>{});
    
    return std::make_pair(true, std::make_unique<Rotate>(rotation));
}

std::pair<bool, std::unique_ptr<ICommand>> InputController::try_process_movement(GLFWwindow* window, float delta)
{
    float cameraSpeed = movement_sense * delta;
    glm::vec3 move{0.0f, 0.0f, 0.0f};
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            move.z += cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            move.z -= cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            move.x += cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            move.x -= cameraSpeed;
    
    if (move.x == 0 && move.z == 0) return std::make_pair(false, std::unique_ptr<ICommand>{});
    
    return std::make_pair(true, std::make_unique<Move>(move));
}
