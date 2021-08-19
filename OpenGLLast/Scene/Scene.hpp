//
//  Scene.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 20.04.2021.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <iostream>

#include <map>
#include <set>

#include "Camera.hpp"
#include "Object.hpp"
#include "ShaderProgram.hpp"
#include "Skybox.hpp"

#include "ILightSource.hpp"

#include "RendererLightSourceHandler.hpp"

class Scene
{
public:
    
    using shaders_to_objects_map = std::map<std::shared_ptr<ShaderProgram>, std::map<int, std::weak_ptr<Object>>>;
    using lights_vec = std::vector<RendererLightSourceHandle>;
    
    Scene(std::shared_ptr<ShaderProgram> std_sh, std::shared_ptr<Camera> camera, std::shared_ptr<ShaderProgram> l_shader, std::shared_ptr<ShaderProgram> o_shader);
    
    bool add_object(std::shared_ptr<Object> obj);
    bool add_object(std::shared_ptr<Object> obj, std::shared_ptr<ShaderProgram> shader);
    
    void set_skybox(std::shared_ptr<Skybox> skybox, std::shared_ptr<ShaderProgram> skybox_shader);
    
    bool add_light(std::shared_ptr<ILightSource> obj);
    
    bool delete_object(int id);
    
    bool set_shader(std::shared_ptr<ShaderProgram> shader_prog, std::shared_ptr<Object> obj);
    
    void pre_cycle_init();
    
    const shaders_to_objects_map& get_shaders_to_objects() const;
    const lights_vec& get_light_sources() const;
    
    std::shared_ptr<ShaderProgram> get_standard_shader() const;
    std::shared_ptr<ShaderProgram> get_light_shader() const;
    std::shared_ptr<ShaderProgram> get_outline_shader() const;
    
    std::shared_ptr<Camera> get_main_camera() const;
    
    std::shared_ptr<Skybox> get_skybox() const;
    std::shared_ptr<ShaderProgram> get_skybox_shader() const;
    
private:
    shaders_to_objects_map shader_to_objects;
    std::shared_ptr<Skybox> skybox;
    
    std::shared_ptr<ShaderProgram> standard_shader;
    std::shared_ptr<ShaderProgram> light_shader;
    std::shared_ptr<ShaderProgram> outline_shader;
    std::shared_ptr<ShaderProgram> skybox_shader;
    
    std::shared_ptr<ShaderProgram> light_map_ortho_shader;
    std::shared_ptr<ShaderProgram> light_map_persp_shader;

    std::shared_ptr<Camera> main_camera;
    
    lights_vec light_sources;
private:
    void clear_removed_object();
    std::pair<bool, std::shared_ptr<ShaderProgram>> is_exists(int id);
};

#endif /* Scene_hpp */
