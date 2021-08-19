//
//  Skybox.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 27.05.2021.
//

#include "Skybox.hpp"


Skybox::Skybox(ObjectData<float> d) :
vao{std::make_unique<VertexArrayObject>()},
vbo{std::make_unique<VertexBufferObject>(GL_ARRAY_BUFFER)},
object_data{std::move(d)}
{
    vao->use_binded([this] ()
    {
        vbo->initialize(object_data.get_data_ref(), true);
    });
}

Skybox::Skybox(const Skybox& o) :
  object_data {o.object_data},
  vao{std::make_unique<VertexArrayObject>()},
  vbo{std::make_unique<VertexBufferObject>(GL_ARRAY_BUFFER)},
  cubemap{o.cubemap}
{
    vao->use_binded([this] ()
    {
        vbo->initialize(object_data.get_data_ref(), true);
    });
}

Skybox& Skybox::operator=(const Skybox& o)
{
    vao = std::make_unique<VertexArrayObject>();
    vbo = std::make_unique<VertexBufferObject>(GL_ARRAY_BUFFER);
    
    object_data = o.object_data;
    
    vao->use_binded([this] ()
    {
        vbo->initialize(object_data.get_data_ref(), true);
    });
    
    cubemap = o.cubemap;
    
    return *this;
}

Skybox::Skybox(Skybox&& o) :
vao {std::move(o.vao)},
vbo {std::move(o.vbo)},
cubemap {std::move(o.cubemap)},
object_data {std::move(o.object_data)}
{
}

Skybox& Skybox::operator=(Skybox&& o)
{
    vao = std::move(o.vao);
    vbo = std::move(o.vbo);
    object_data = std::move(o.object_data);
    cubemap = std::move(o.cubemap);
    
    return *this;
}

Skybox& Skybox::set_cubemap(std::shared_ptr<ITexture> t)
{
    cubemap = t;
    
    return *this;
}

std::shared_ptr<ITexture> Skybox::get_cubemap()
{
    return cubemap;
}

VertexArrayObject* Skybox::get_vao() const
{
    return vao.get();
}

VertexBufferObject* Skybox::get_vbo() const
{
    return vbo.get();
}

ObjectData<float>* Skybox::get_object_data()
{
    return &object_data;
}
