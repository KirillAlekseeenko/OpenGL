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

#include "ObjectData.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"

#include "IDebugObject.hpp"

/*
 
 It's the object for displaying vectors (ex. normals)
 
 */

class Vector : public IDebugObject
{
public:
    Vector();
    
    Vector(const Vector& v) = delete;
    Vector& operator=(const Vector& v) = delete;
    
    glm::vec3 get_origin() const {return origin;}
    glm::vec3 get_direction() const {return direction;}
    glm::vec3 get_color() const {return color;}
    
    glm::mat4 get_position() const {return position;}
    
    Vector& set_positon(glm::vec3 o, glm::vec3 d);
    Vector& set_color(glm::vec3 c);
    
    ObjectData<float>* get_data();
    
    VertexArrayObject* get_vao();
    VertexBufferObject* get_vbo();
    
    /*
     
     create object as a field
     create debug shader for drawing lights, vectors on the scene
     
     */
    
    void draw(IRenderer* renderer, std::shared_ptr<ShaderProgram> shader) override;
private:
    
    glm::vec3 origin;
    glm::vec3 direction;
    
    glm::mat4 position {1.0f};
    glm::vec3 color {1.0f, 0.0f, 0.0f};
    
    ObjectData<float> data;
    
    VertexArrayObject vao;
    VertexBufferObject vbo;
    
    GLint model_uniform = 0;
    GLint color_uniform = 0;
    
    bool is_ready_for_drawing = false;
    
};

#endif /* Vector_hpp */
