//
//  Vector.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 18.04.2021.
//

#ifndef Vector_hpp
#define Vector_hpp

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "ShaderProgram.hpp"
#include "ObjectData.hpp"
#include "VertexArrayObject.hpp"

class Vector
{
public:
    Vector(std::shared_ptr<ShaderProgram> s);
    
    glm::vec3 get_origin() const {return origin;}
    glm::vec3 get_direction() const {return direction;}
    glm::vec3 get_color() const {return color;}
    
    Vector& set_positon(glm::vec3 o, glm::vec3 d);
    Vector& set_color(glm::vec3 c);
    
    void draw();
private:
    glm::vec3 origin;
    glm::vec3 direction;
    
    glm::mat4 position {1.0f};
    glm::vec3 color {1.0f, 0.0f, 0.0f};
    
    std::shared_ptr<ShaderProgram> shader;
    ObjectData<float> data;
    
    VertexArrayObject vao;
    VertexBufferObject vbo;
    
    GLint model_uniform = 0;
    GLint color_uniform = 0;
    
    bool is_ready_for_drawing = false;
    
};

#endif /* Vector_hpp */
