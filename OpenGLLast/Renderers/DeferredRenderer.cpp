//
//  DeferredRenderer.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.05.2021.
//

#include "DeferredRenderer.hpp"

#include "Scene.hpp"



void DeferredRenderer::draw(Object* o, ShaderProgram* shader)
{
    
}

void DeferredRenderer::draw_outlined(Object* o, ShaderProgram *shader, ShaderProgram* outline_shader)
{
    
}

void DeferredRenderer::draw_vector(Vector *v, ShaderProgram *shader)
{
    
}

void DeferredRenderer::draw_scene(const Scene &scene)
{
    auto main_camera = scene.get_main_camera();
    
    auto outline_shader = scene.get_outline_shader();
    auto light_shader = scene.get_light_shader();
    
    auto& shader_to_objects = scene.get_shaders_to_objects();
    auto& light_sources = scene.get_light_sources();
    
    
    
    /*
     1. render data to g-buffer
     2. perform lighting passes
     */
}


