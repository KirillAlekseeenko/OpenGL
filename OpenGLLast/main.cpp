//
//  main.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 10.04.2021.
//

#define GL_SILENCE_DEPRECATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "Shader.hpp"
#include "ShaderProgram.hpp"

#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "Texture.hpp"

#include "Object.hpp"
#include "ObjectData.hpp"

#include "Camera.hpp"
#include "Move.hpp"
#include "Rotate.hpp"

#include "Presets.hpp"

#include "InputController.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int lib_init(GLFWwindow* &window);
void main_actions(GLFWwindow* window);
void clean_up();

int main()
{
    GLFWwindow* window = nullptr;
    auto r = lib_init(window);
    
    if (r != 0 || window == nullptr)
    {
        clean_up();
        return r;
    }
    
    try
    {
        main_actions(window);
    }
    catch(...)
    {
        clean_up();
    }
    
    clean_up();
    
    return 0;
}

int lib_init(GLFWwindow* &w)
{
    GLFWwindow* window;
    
    if(!glfwInit())
        return -1;

    // Initialize the library
    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    // Create a windowed mode window and its OpenGL context
    // GLFWmonitor is needed if you want to make full screen window (if you do, supply this function with your primary monitor)
    // GLFWwindow is needed to set window that will share the context created by this function (see Context Object Sharing)
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        const char* description;
        auto code = glfwGetError(&description);
        std::cout << "Error code: " << code << std::endl;
        std::cout << "Description: " << description << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Mathe the window's context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto err = glewInit();
    
    if (err != GLEW_OK)
    {
        std::cout << "\nGLEW initialization failed, error code: " << err << ", description: " << glewGetErrorString(err) << "\n";
        return -1;
    }
    
    w = window;
    
    return 0;
}

void main_actions(GLFWwindow* window)
{
    glEnable(GL_DEPTH_TEST);
    
    InputController input_controller;
    
    auto camera = std::make_shared<Camera>();
    camera->set_postion(glm::vec3(0.0f, 0.0f, 2.0f));
    
    auto program = std::make_shared<ShaderProgram>(Shader(GL_VERTEX_SHADER, "tri_vertex.glsl"), Shader(GL_FRAGMENT_SHADER, "tri_fragment.glsl"));
    
    auto shifted_color_program = std::make_shared<ShaderProgram>(Shader(GL_VERTEX_SHADER, "tri_vertex_2.glsl"), Shader(GL_FRAGMENT_SHADER, "tri_fragment_2.glsl"));
    
    auto result = program->link();
    if (std::get<0>(result) == GL_FALSE)
    {
        return;
    }
    
    result = shifted_color_program->link();
    if (std::get<0>(result) == GL_FALSE)
    {
        return;
    }
    
    auto texture = std::make_shared<Texture>("wall.jpg");

    if (!texture->is_valid())
    {
        std::cout << "texture is invalid";
        
        return;
    }
    
    auto texture_basement = std::make_shared<Texture>("basement.jpg");

    if (!texture_basement->is_valid())
    {
        std::cout << "texture is invalid";
        
        return;
    }
    
    auto pyramid_data = ObjectData<float>{};
    
    pyramid_data
        .set_data(get_pyramide())
        .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0})
        .set_attribute_pointer(AttributePointer{1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))})
        .set_attribute_pointer(AttributePointer{2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))});
    
    Object pyramid{shifted_color_program, pyramid_data};
    
    glm::mat4 model {1.0f};
    
    pyramid.set_texture(texture);
    
    auto light_data = ObjectData<float>::create_data()
    .set_data(get_light_cube())
    .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0})
    .set_attribute_pointer(AttributePointer{1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))});
    
    Object light {shifted_color_program, light_data};
    
    light.set_position(glm::translate(model, glm::vec3(2.0f, 2.0f, 2.0f)));
    
    shifted_color_program->use();
    
    shifted_color_program->set_view_mat(camera->get_look_at());
    shifted_color_program->set_projection_mat(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f , 0.1f, 100.0f));

    std::cout << "OpenGL version: " << glGetString(GL_VERSION);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    //auto model_uniform = program->get_uniform_location("model");
    
    auto last_frame = 0.0f;
    auto current_frame = 0.0f;
    
    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        current_frame = glfwGetTime();
        
        auto delta = current_frame - last_frame;
        last_frame = current_frame;
        
        auto movement_command = input_controller.try_process_movement(window, delta);
        if (movement_command.first)
        {
            movement_command.second->execute(camera);
        }
        
        auto view_command = input_controller.try_process_view(window, delta);
        if (view_command.first)
        {
            view_command.second->execute(camera);
        }
        
        // Render here!
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        shifted_color_program->set_view_mat(camera->get_look_at());
        
        pyramid.draw();
        light.draw();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
}

void clean_up()
{
    glfwTerminate();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina displays
    glViewport(0, 0, width, height);
}
