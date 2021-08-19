//
//  ForwardRenderer.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.05.2021.
//

#include "ForwardRenderer.hpp"

#include "Scene.hpp"
#include "ShaderProgram.hpp"
#include "Vector.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Meta.hpp"

#include "ShaderLightArrayAdapter.hpp"


void ForwardRenderer::draw(Object* o, ShaderProgram* shader)
{
    __drawObject(o, shader);
}

void ForwardRenderer::draw_vector(Vector *v, ShaderProgram *shader)
{
    auto data = *(v->get_data());
    
    auto vbo = v->get_vbo();
    auto vao = v->get_vao();
    
    if (!data.validate()) throw std::runtime_error{"object_data is invalid"};
    
    auto model_uniform = shader->get_uniform_location("model");
    //auto color_uniform = shader->get_uniform_location("color");
    
    auto color = v->get_color();
    auto position = v-> get_position();
    
    vao->use_binded([this, &data, vbo]()
    {
        for (const auto& attr : data.get_attributes_ref())
        {
            vbo->set_attrib_pointer(attr.index, attr.size_per_vertex, attr.type, attr.normalized, attr.stride, attr.offset);
        }
    });
    
    shader->use();
    
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(position));
    //glUniform3fv(color_uniform, 1, glm::value_ptr(color));
    
    vao->use_binded([this, &data]()
    {
        int begin = 0;
        int count = data.get_vertex_count();
        
        glEnable(GL_LINE_SMOOTH);
        
        glDrawArrays(GL_LINES, begin, count - 1);
        
        glDisable(GL_LINE_SMOOTH);
        glDrawArrays(GL_POINTS, count - 1, 1);
    });
}

void ForwardRenderer::draw_outlined(Object* o, ShaderProgram *shader, ShaderProgram* outline_shader)
{
    __drawObject(o, shader, outline_shader);
}

void ForwardRenderer::__drawSkybox(Skybox* skybox, ShaderProgram* skybox_shader)
{
    auto vao = skybox->get_vao();
    auto vbo = skybox->get_vbo();
    
    auto object_data = *(skybox->get_object_data());
    
    auto cubemap = skybox->get_cubemap();
    
    vao->use_binded([&object_data, vbo]()
    {
        for (const auto& attr : object_data.get_attributes_ref())
        {
            vbo->set_attrib_pointer(attr.index, attr.size_per_vertex, attr.type, attr.normalized, attr.stride, attr.offset);
        }
    });
    
    skybox_shader->use();
    skybox_shader->set_map_uniform(TextureType::Cubemap);
    
    vao->use_binded([&object_data, &cubemap]()
    {
        auto v_count = object_data.get_vertex_count();
        
        glActiveTexture(GL_TEXTURE0 + static_cast<int>(to_underlying(TextureType::Cubemap)));
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->get_handle());
        
        glDepthFunc(GL_LEQUAL);
        
        glDrawArrays(GL_TRIANGLES, 0, v_count);
        
        glDepthFunc(GL_LESS);
    });
}

void ForwardRenderer::__drawObject(Object *o, ShaderProgram *shader, ShaderProgram* outline_shader)
{
    auto vao = o->get_vao();
    auto vbo = o->get_vbo();
    
    auto object_data = *(o->get_object_data());
    
    auto& maps = o->get_all_maps();
    
    auto position = o->get_position();
    
    if (!object_data.validate()) throw std::runtime_error{"object_data is invalid"};
    
    auto model_uniform = shader->get_uniform_location("model");       // TODO: maybe parse uniforms during before compilation?
    
    vao->use_binded([&object_data, vbo]()
    {
        for (const auto& attr : object_data.get_attributes_ref())
        {
            vbo->set_attrib_pointer(attr.index, attr.size_per_vertex, attr.type, attr.normalized, attr.stride, attr.offset);
        }
    });
    
    shader->use();
    
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(position));
    
    for (auto i = 0; i < maps.size(); i++)
    {
        shader->set_map_uniform(static_cast<TextureType>(i));
    }
    
    
    vao->use_binded([&object_data, &maps, &outline_shader, &position]()
    {
        int begin = 0;
        int count = object_data.get_vertex_count();
        
        for (auto i = 0; i < maps.size(); i++)
        {
            auto map = maps[i];
            
            if (map)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, map->get_handle());
            }
        }
        
        if (outline_shader)                                   // TODO: make lambdas
        {
            glStencilMask(0xFF);                                                                     // fill stencil buffer with 1s
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        }
        
        glDrawArrays(GL_TRIANGLES, begin, count);
        
        if (outline_shader)
        {
            glStencilMask(0x00);
            //glDisable(GL_DEPTH_TEST);
            glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
            
            outline_shader->use();
            auto current_pos = glm::scale(position, glm::vec3(1.03f, 1.03f, 1.03f));
            auto outlined_model_uniform = outline_shader->get_uniform_location("model");
            glUniformMatrix4fv(outlined_model_uniform, 1, GL_FALSE, glm::value_ptr(current_pos));
            
            glDrawArrays(GL_TRIANGLES, begin, count);
            
            //glEnable(GL_DEPTH_TEST);
            
            glStencilFunc(GL_ALWAYS, 1, 0xFF);
            
        }
    });
}

void ForwardRenderer::draw_scene(const Scene &scene)
{
    auto main_camera = scene.get_main_camera();
    
    auto outline_shader = scene.get_outline_shader();
    auto light_shader = scene.get_light_shader();
    
    auto& shader_to_objects = scene.get_shaders_to_objects();
    auto& light_sources = scene.get_light_sources();
    
    auto skybox = scene.get_skybox();
    auto skybox_shader = scene.get_skybox_shader();
    
    if (skybox_shader)
    {
        skybox_shader->use();
        skybox_shader->set_view_mat(main_camera->get_look_at());
    }
    
    if (outline_shader.get() != nullptr)
    {
        outline_shader->use();
        outline_shader->set_view_mat(main_camera->get_look_at());
    }
    
    for (const auto& c : shader_to_objects)                       // TODO: implement clipping
    {
        auto shader = c.first;
        
        if (c.second.size() > 0)                                  // setting light prmtrs
        {
            shader->use();
            
            shader->set_camera_pos(main_camera->get_position());
            shader->set_view_mat(main_camera->get_look_at());
            
            std::unique_ptr<IShaderLightAdapter> shader_light_adapter = std::make_unique<ShaderLightArrayAdapter>(shader.get());
            
            for (const auto& light : light_sources)
            {
                auto light_shader_helper = light.get_light()->get_shader_helper();
                light_shader_helper->apply(shader_light_adapter.get());
            }
        }
        
        for (auto& p : c.second)                          // objects drawing
        {
            if (auto obj = p.second.lock())
            {
                auto& draw_prms = obj->get_draw_parameters();
                
                if (draw_prms.outlined)                                                     // TODO: reformat to more sophisticated way
                {
                    draw_outlined(obj.get(), shader.get(), outline_shader.get());
                }
                else
                {
                    draw(obj.get(), shader.get());
                }
            }
        }
    }
    
    // draw debug obj
    
    
    if (light_shader.get() != nullptr)
    {
        light_shader->use();
        light_shader->set_view_mat(main_camera->get_look_at());
        
        for (const auto& light : light_sources)
        {
            auto light_visual = light.get_light()->get_visual_source();
            light_visual->draw(this, light_shader);
        }
    }
    
    if (skybox_shader && skybox)
    {
        skybox_shader->use();
        
        __drawSkybox(skybox.get(), skybox_shader.get());
    }
}
