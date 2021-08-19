//
//  Vector.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 18.04.2021.
//

#include "Vector.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

#include "IRenderer.hpp"

Vector::Vector() : data{}, vao{}, vbo{GL_ARRAY_BUFFER}
{
    data.set_data(std::vector<float> {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        
        // arrow
        
        0.0f, 0.0f, 1.0f,
        0.0f, 0.03f, 0.7f,
        
        0.0f, 0.0f, 1.0f,
        0.0f, -0.03f, 0.7f,
        
        0.0f, 0.0f, 1.0f,
        0.03f, 0.0f, 0.7f,
        
        0.0f, 0.0f, 1.0f,
        -0.03f, 0.0f, 0.7f,
        
        0.0f, 0.0f, 1.0f,
        0.03f, 0.03f, 0.7f,
        
        0.0f, 0.0f, 1.0f,
        0.03f, -0.03f, 0.7f,
        
        0.0f, 0.0f, 1.0f,
        -0.03f, -0.03f, 0.7f,
        
        0.0f, 0.0f, 1.0f,
        -0.03f, 0.03f, 0.7f,
        
        // tip
        
        0.0f, 0.0f, 1.0f
    })
    .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0});
    
    vao.use_binded([this]()
    {
        vbo.initialize(data.get_data_ref(), true);
    });
}

Vector& Vector::set_positon(glm::vec3 o, glm::vec3 d)
{
    auto norm_d = glm::normalize(d);
    
    origin = o;
    direction = norm_d;
    
    auto z_vec = glm::vec3(0.0f, 0.0f, 1.0f);
    
    auto cos_a = glm::dot(z_vec, norm_d);
    auto cross = glm::cross(z_vec, norm_d);
    
    auto sin_a = glm::length(cross);
    
    float angle;
    glm::mat4 rotate_m {1.0f};
    glm::mat4 translate_m {1.0f};
    
    if (sin_a != 0)
    {
        auto a_cos = acos(cos_a);
        
        angle = sin_a >= 0 ? a_cos : M_PI * 2 - a_cos;
        
        rotate_m = glm::rotate(rotate_m, angle, cross);
        
    }
    else
    {
        if (cos_a < 0)
        {
            angle = M_PI;
            rotate_m = glm::rotate(rotate_m, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
    
    translate_m = glm::translate(translate_m, o);
    
    position = translate_m * rotate_m;
    
    return *this;
}

Vector& Vector::set_color(glm::vec3 c)
{
    color = c;
    
    return *this;
}

void Vector::draw(IRenderer* renderer, std::shared_ptr<ShaderProgram> shader)
{
    renderer->draw_vector(this, shader.get());
}

ObjectData<float>* Vector::get_data()
{
    return &data;
}

VertexArrayObject* Vector::get_vao()
{
    return &vao;
}

VertexBufferObject* Vector::get_vbo()
{
    return &vbo;
}
