//
//  Object.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 13.04.2021.
//

#ifndef Object_hpp
#define Object_hpp

#include "ShaderProgram.hpp"
#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Texture.hpp"
#include "ObjectData.hpp"
#include "Camera.hpp"

#include "AuxiliaryTexture.hpp"

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

class Object
{
public:
    Object(std::shared_ptr<ShaderProgram> p, ObjectData<float> d);
    
    Object(const Object& o);
    Object& operator=(const Object& o);
    
    Object(Object&& o);
    Object& operator=(Object&& o);
    
    Object& edit_vbo(std::function<void(VertexBufferObject& vbo)>);
    void draw();
    
    Object& set_position(glm::mat4 pos);
    glm::mat4 get_position();
    
    Object& set_shader(std::shared_ptr<ShaderProgram> sd);
    std::shared_ptr<ShaderProgram> get_shader();
    
    Object& set_texture(std::shared_ptr<Texture> t);
    std::shared_ptr<Texture> get_texture();
    
private:
    VertexArrayObject vao;
    VertexBufferObject vbo;
    
    std::shared_ptr<ShaderProgram> program;
    
    glm::mat4 position {1.0f};
    
    ObjectData<float> object_data;
    
    std::shared_ptr<Texture> texture;
    
    // RUNTIME PROPS
    
    bool is_ready_for_drawing = false;
    
    GLint model_uniform = 0;
    GLint texture_uniform = 0;
    
};

#endif /* Object_hpp */
