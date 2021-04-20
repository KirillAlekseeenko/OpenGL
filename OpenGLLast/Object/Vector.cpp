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

glm::mat4 huyevaya_versiya(glm::vec3 o, glm::vec3 d)
{
    auto norm_d = glm::normalize(d);
    
    float rot_m_data[] = {
        0.0f, 0.0f, norm_d.x, 0.0f,
        0.0f, 0.0f, norm_d.y, 0.0f,
        0.0f, 0.0f, norm_d.z, 0.0f,
        0.0f, 0.0f, 0.0f,   1.0f,
    };
    
    glm::mat4 rot_m;
    std::memcpy(glm::value_ptr(rot_m), rot_m_data, sizeof(rot_m_data));
    rot_m = glm::transpose(rot_m);
    
    glm::mat4 translate_m {1.0f};
    translate_m = glm::translate(translate_m, o);
    
    return translate_m * rot_m;
}

Vector::Vector(std::shared_ptr<ShaderProgram> s) : shader {s}, data{}, vao{}, vbo{GL_ARRAY_BUFFER}
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
    
    vao.use_binded([this] ()
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

void Vector::draw()
{
    if (!is_ready_for_drawing)
    {
        if (!data.validate()) throw std::runtime_error{"object_data is invalid"};
        
        model_uniform = shader->get_uniform_location("model");
        color_uniform = shader->get_uniform_location("color");
        
        vao.use_binded([this]()
        {
            for (const auto& attr : data.get_attributes_ref())
            {
                vbo.set_attrib_pointer(attr.index, attr.size_per_vertex, attr.type, attr.normalized, attr.stride, attr.offset);
            }
        });
        
        
        is_ready_for_drawing = true;
    }
    
    shader->use();
    
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(position));
    glUniform3fv(color_uniform, 1, glm::value_ptr(color));
    
    vao.use_binded([this]()
    {
        int begin = 0;
        int count = data.get_vertex_count();
        
        glEnable(GL_LINE_SMOOTH);
        
        glDrawArrays(GL_LINES, begin, count - 1);
        
        glDisable(GL_LINE_SMOOTH);
        glDrawArrays(GL_POINTS, count - 1, 1);
    });
}
