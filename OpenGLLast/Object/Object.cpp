//
//  Object.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 13.04.2021.
//

#include <exception>
#include "Object.hpp"

#include <glm/gtc/type_ptr.hpp>

Object::Object(std::shared_ptr<ShaderProgram> p, ObjectData<float> d) :
vao{},
vbo{GL_ARRAY_BUFFER},           // for simplicity took array buffer
program{p},
object_data{std::move(d)}
{
    vao.use_binded([this] ()
    {
        vbo.initialize(object_data.get_data_ref(), true);
    });
}

Object::Object(const Object& o)
: program{o.program},
  object_data {o.object_data},
  vao{},
  vbo{GL_ARRAY_BUFFER},
  texture{o.texture}
{
    vao.use_binded([this] ()
    {
        vbo.initialize(object_data.get_data_ref(), true);
    });
}

Object& Object::operator=(const Object& o)
{
    vao = VertexArrayObject{};
    vbo = VertexBufferObject{GL_ARRAY_BUFFER};
    
    object_data = o.object_data;
    program = o.program;
    
    vao.use_binded([this] ()
    {
        vbo.initialize(object_data.get_data_ref(), true);
    });
    
    texture = o.texture;
    
    return *this;
}

Object::Object(Object&& o)
: vao{std::move(o.vao)},
  vbo{std::move(o.vbo)},
  object_data{std::move(o.object_data)},
  program{o.program},
  texture{o.texture}
{
    
}

Object& Object::operator=(Object&& o)
{
    vao = std::move(o.vao);
    vbo = std::move(o.vbo);
    object_data = std::move(o.object_data);
    program = o.program;
    texture = o.texture;
    
    return *this;
}

Object& Object::edit_vbo(std::function<void(VertexBufferObject& vbo)> f)
{
    vao.use_binded([this, &f]()
    {
        f(vbo);
    });
    
    return *this;
}

void Object::draw()
{
    if (!is_ready_for_drawing)
    {
        if (!object_data.validate()) throw std::runtime_error{"object_data is invalid"};
        
        model_uniform = program->get_uniform_location("model");       // TODO: maybe parse uniforms during before compilation?
        
        if (texture.get() != nullptr)
        {
            texture_uniform = program->get_uniform_location("texture0");
        }
        
        vao.use_binded([this]()
        {
            for (const auto& attr : object_data.get_attributes_ref())
            {
                vbo.set_attrib_pointer(attr.index, attr.size_per_vertex, attr.type, attr.normalized, attr.stride, attr.offset);
            }
        });
        
        is_ready_for_drawing = true;
    }
    
    program->use();
    
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(position));
    
    vao.use_binded([this]()
    {
        int begin = 0;
        int count = object_data.get_vertex_count();
        
        if (texture.get() != nullptr)
        {
            //glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->get_handle());
        }
        
        glDrawArrays(GL_TRIANGLES, begin, count);
    });
}

Object& Object::set_position(glm::mat4 pos)
{
    position = pos;
    
    return *this;
}

glm::mat4 Object::get_position()
{
    return position;
}

Object& Object::set_shader(std::shared_ptr<ShaderProgram> sd)
{
    program = sd;
    
    return *this;
}

std::shared_ptr<ShaderProgram> Object::get_shader()
{
    return program;
}

Object& Object::set_texture(std::shared_ptr<Texture> s)
{
    texture = s;
    
    return *this;
}

std::shared_ptr<Texture> Object::get_texture()
{
    return texture;
}
