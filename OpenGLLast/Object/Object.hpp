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

#include "Actor.hpp"

class Object : public IActor
{
public:
    Object(std::shared_ptr<ShaderProgram> p, ObjectData<float> d);            // TODO: need to store vec3 position (for light)
    
    Object(const Object& o);
    Object& operator=(const Object& o);
    
    Object(Object&& o);
    Object& operator=(Object&& o);
    
    Object& edit_vbo(std::function<void(VertexBufferObject& vbo)>);
    void draw();
    
    Object& translate(glm::vec3 v);
    Object& rotate(float angle, glm::vec3 axis);
    Object& scale(glm::vec3 s);
    
    glm::mat4 get_position();
    glm::vec3 get_world_position();
    
    Object& set_shader(std::shared_ptr<ShaderProgram> sd);
    std::shared_ptr<ShaderProgram> get_shader();
    
    Object& set_texture(std::shared_ptr<Texture> t);
    std::shared_ptr<Texture> get_texture();
    
    void move_offset(glm::vec3 offset) override;
    void rotate_offset(glm::vec3 offset) override;
    
private:
    VertexArrayObject vao;
    VertexBufferObject vbo;
    
    std::shared_ptr<ShaderProgram> program;
    
    glm::mat4 position {1.0f};
    
    glm::vec3 world_position {0.0f, 0.0f, 0.0f};
    
    ObjectData<float> object_data;
    
    std::shared_ptr<Texture> texture;
    
    // RUNTIME PROPS
    
    bool is_ready_for_drawing = false;
    
    GLint model_uniform = 0;
    GLint texture_uniform = 0;
    
};

#endif /* Object_hpp */
