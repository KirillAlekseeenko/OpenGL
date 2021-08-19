//
//  Scene.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 20.04.2021.
//

#include "Scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderLightArrayAdapter.hpp"


Scene::Scene(std::shared_ptr<ShaderProgram> std_sh, std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> l_shader, std::shared_ptr<ShaderProgram> o_shader)
: standard_shader {std_sh},
main_camera{camera},
light_shader{l_shader},
outline_shader{o_shader}
{
}

bool Scene::add_object(std::shared_ptr<Object> obj)
{
    return add_object(obj, standard_shader);
}

bool Scene::add_object(std::shared_ptr<Object> obj, std::shared_ptr<ShaderProgram> shader)
{
    if (is_exists(obj->get_id()).first) return false;
    
    auto shader_objects = shader_to_objects.find(shader);
    
    if (shader_objects != shader_to_objects.end())
    {
        shader_objects->second[obj->get_id()] = obj;
        return true;
    }
    
    std::map<int, std::weak_ptr<Object>> new_shader_map {};
    
    new_shader_map[obj->get_id()] = obj;
    
    shader_to_objects[shader] = std::move(new_shader_map);
    
    return true;
}

bool Scene::add_light(std::shared_ptr<ILightSource> obj)
{
    light_sources.push_back(obj);
    return true;
}

bool Scene::delete_object(int id)
{
    auto exists = is_exists(id);
    
    if (!exists.first) return false;
    
    auto shader = exists.second;
    auto shader_objects = shader_to_objects.find(shader);
    
    if (shader_objects != shader_to_objects.end())
    {
        shader_objects->second.erase(id);
    }
    
    return true;
}

void Scene::pre_cycle_init()
{
    for (const auto& c : shader_to_objects)
    {
        auto shader = c.first;
        
        shader->use();
        
        shader->set_projection_mat(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f , 0.1f, 100.0f));        // default
        shader->set_ambient_strength(0.1f);
        shader->set_height_scale(0.1f);
        
        shader->set_camera_pos(main_camera->get_position());
        shader->set_view_mat(main_camera->get_look_at());
        
        std::unique_ptr<IShaderLightAdapter> shader_light_adapter = std::make_unique<ShaderLightArrayAdapter>(shader.get());
        
        for (const auto& light : light_sources)
        {
            auto light_shader_helper = light.get_light()->get_shader_helper();
            light_shader_helper->apply(shader_light_adapter.get());
        }
    }
    
    /*for (auto& light : light_sources)
    {
        light.load_to_vram();
    }
     */
    
    if (light_shader.get() != nullptr)
    {
        light_shader->use();
        light_shader->set_view_mat(main_camera->get_look_at());
        light_shader->set_projection_mat(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f , 0.1f, 100.0f));
    }
    
    if (outline_shader.get() != nullptr)
    {
        outline_shader->use();
        outline_shader->set_view_mat(main_camera->get_look_at());
        outline_shader->set_projection_mat(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f , 0.1f, 100.0f));
        
        outline_shader->set_outline_color(glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    if (skybox_shader)
    {
        skybox_shader->use();
        skybox_shader->set_projection_mat(glm::perspective(glm::radians(45.0f), 640.0f / 480.0f , 0.1f, 100.0f));
    }
}

void Scene::clear_removed_object()
{
    for (auto& p : shader_to_objects)
    {
        for (auto iter = p.second.begin(); iter != p.second.end();)
        {
            if (!iter->second.lock())
            {
                iter = p.second.erase(iter);
            }
            else
            {
                iter++;
            }
        }
    }
}

std::pair<bool, std::shared_ptr<ShaderProgram>> Scene::is_exists(int id)
{
    for (const auto& p : shader_to_objects)
    {
        auto obj_iter = p.second.find(id);
        if (obj_iter != p.second.end())
        {
            return std::make_pair(true, p.first);
        }
    }
    
    return std::make_pair(false, std::shared_ptr<ShaderProgram>());
}

const Scene::shaders_to_objects_map& Scene::get_shaders_to_objects() const
{
    return shader_to_objects;
}
const Scene::lights_vec& Scene::get_light_sources() const
{
    return light_sources;
}

std::shared_ptr<ShaderProgram> Scene::get_standard_shader() const
{
    return standard_shader;
}

std::shared_ptr<ShaderProgram> Scene::get_light_shader() const
{
    return light_shader;
}

std::shared_ptr<ShaderProgram> Scene::get_outline_shader() const
{
    return outline_shader;
}

std::shared_ptr<Camera> Scene::get_main_camera() const
{
    return main_camera;
}

std::shared_ptr<Skybox> Scene::get_skybox() const
{
    return skybox;
}
std::shared_ptr<ShaderProgram> Scene::get_skybox_shader() const
{
    return skybox_shader;
}

void Scene::set_skybox(std::shared_ptr<Skybox> s, std::shared_ptr<ShaderProgram> s_shader)
{
    skybox = s;
    skybox_shader = s_shader;
}
