//
//  Object.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 13.04.2021.
//

#include <exception>
#include "Object.hpp"
#include "Meta.hpp"

#include <glm/gtc/type_ptr.hpp>

Object::Object(ObjectData<float> d) :                     // TODO: remove shader 'program' field
vao{std::make_unique<VertexArrayObject>()},
vbo{std::make_unique<VertexBufferObject>(GL_ARRAY_BUFFER)},           // for simplicity took array buffer
object_data{std::move(d)}
{
    vao->use_binded([this] ()
    {
        vbo->initialize(object_data.get_data_ref(), true);
    });
}

Object::Object(const Object& o)
: object_data {o.object_data},
  vao{std::make_unique<VertexArrayObject>()},
  vbo{std::make_unique<VertexBufferObject>(GL_ARRAY_BUFFER)},
  maps{o.maps},
draw_parameters {o.draw_parameters}
{
    vao->use_binded([this] ()
    {
        vbo->initialize(object_data.get_data_ref(), true);
    });
}

Object& Object::operator=(const Object& o)
{
    vao = std::make_unique<VertexArrayObject>();
    vbo = std::make_unique<VertexBufferObject>(GL_ARRAY_BUFFER);
    
    object_data = o.object_data;
    draw_parameters = o.draw_parameters;
    
    vao->use_binded([this] ()
    {
        vbo->initialize(object_data.get_data_ref(), true);
    });
    
    maps = o.maps;
    
    return *this;
}

Object::Object(Object&& o)
: vao{std::move(o.vao)},
  vbo{std::move(o.vbo)},
  object_data{std::move(o.object_data)},
maps{std::move(o.maps)},
draw_parameters {o.draw_parameters}
{
    
}

Object& Object::operator=(Object&& o)
{
    vao = std::move(o.vao);
    vbo = std::move(o.vbo);
    object_data = std::move(o.object_data);
    maps = std::move(o.maps);
    draw_parameters = o.draw_parameters;
    
    return *this;
}

Object& Object::edit_vbo(std::function<void(VertexBufferObject* vbo)> f)
{
    vao->use_binded([this, &f]()
    {
        f(vbo.get());
    });
    
    return *this;
}

Object& Object::translate(glm::vec3 v)
{
    world_position += v;
    translation_matrix = glm::translate(translation_matrix, v);
    
    return *this;
}

Object& Object::set_world_position(glm::vec3 v)
{
    world_position = v;
    translation_matrix = glm::translate(glm::mat4{1.0f}, v);
    
    return *this;
}

Object& Object::rotate(float angle, glm::vec3 axis)
{
    rotation_matrix = glm::rotate(rotation_matrix, angle, axis);
    
    return *this;
}

Object& Object::scale(glm::vec3 s)
{
    scale_matrix = glm::scale(scale_matrix, s);
    
    return *this;
}

glm::mat4 Object::get_position()
{
    return translation_matrix * rotation_matrix * scale_matrix;
}

glm::vec3 Object::get_world_position()
{
    return world_position;
}

Object& Object::set_diffuse(std::shared_ptr<ITexture> t)
{
    return set_texture(std::move(t), TextureType::Diffuse);
}

std::shared_ptr<ITexture> Object::get_diffuse()
{
    return get_texture(TextureType::Diffuse);
}

Object& Object::set_normal_map(std::shared_ptr<ITexture> t)
{
    return set_texture(std::move(t), TextureType::Normal);
}
std::shared_ptr<ITexture> Object::get_normal_map()
{
    return get_texture(TextureType::Normal);
}

Object& Object::set_specular_map(std::shared_ptr<ITexture> t)
{
    return set_texture(std::move(t), TextureType::Specular);
}

std::shared_ptr<ITexture> Object::get_specular_map()
{
    return get_texture(TextureType::Specular);
}

Object& Object::set_disp_map(std::shared_ptr<ITexture> t)
{
    return set_texture(std::move(t), TextureType::Displacement);
}

std::shared_ptr<ITexture> Object::get_disp_map()
{
    return get_texture(TextureType::Displacement);
}

Object::maps_arr& Object::get_all_maps()
{
    return maps;
}

Object& Object::set_texture(std::shared_ptr<ITexture> &&t, TextureType type)
{
    maps[to_underlying(type)] = t;
    return *this;
}

std::shared_ptr<ITexture> Object::get_texture(TextureType type)
{
    return maps[to_underlying(type)];
}


// IActor

void Object::move_offset(glm::vec3 offset)
{
    translate(offset);
}

void Object::rotate_offset(glm::vec3 offset)           // TODO: rotation axis to rotate random object
{
    
}

VertexArrayObject* Object::get_vao() const
{
    return vao.get();
}

VertexBufferObject* Object::get_vbo() const
{
    return vbo.get();
}

ObjectData<float>* Object::get_object_data()
{
    return &object_data;
}

DrawParameters& Object::get_draw_parameters()
{
    return draw_parameters;
}

std::shared_ptr<Object> Object::create_dir_light_obj()
{
    throw std::runtime_error("not implemented");
}
