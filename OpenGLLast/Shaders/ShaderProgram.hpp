//
//  ShaderProgram.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include "Shader.hpp"
#include <glm/glm.hpp>

#include "TextureType.hpp"
#include <array>

#include "Path.hpp"

class ShaderProgram
{                                                // TODO: check is shader or shader program is compile or linked before usage
public:
    enum ShaderType {Vertex, Fragment};
    
    template<class... Targs>
    ShaderProgram(Targs&&... args)
    {
        handle = glCreateProgram();
        
        init_pipeline(std::forward<Targs>(args)...);
    }
    
    ~ShaderProgram();
    
    ShaderProgram(const ShaderProgram& s) = delete;
    ShaderProgram& operator=(const ShaderProgram& s) = delete;
    
    ShaderProgram(ShaderProgram&& s);
    ShaderProgram& operator=(ShaderProgram&& s);
    
    std::pair<GLint, std::basic_string<GLchar>> link();
    
    GLint get_uniform_location(std::string name) const;
    
    bool use();
    
    GLuint get_handle() const
    {
        return handle;
    }
    
    ShaderProgram& set_projection_mat(glm::mat4 m);
    ShaderProgram& set_view_mat(glm::mat4 m);
    
    ShaderProgram& set_camera_pos(glm::vec3 p);
    ShaderProgram& set_light_pos(glm::vec3 p);
    ShaderProgram& set_ambient_strength(float s);
    ShaderProgram& set_height_scale(float s);
    ShaderProgram& set_outline_color(glm::vec3 v);
    
    static std::unique_ptr<ShaderProgram> create_shader(Dir dir, std::string vertex_local_path, std::string fragment_local_path);
    static std::unique_ptr<ShaderProgram> create_shader(std::string vertex_abs_path, std::string fragment_abs_path);
    
    ShaderProgram& set_map_uniform(TextureType type);
    
    
    // light interface
    
    ShaderProgram& set_dir_light_direction(glm::vec3 d);
    ShaderProgram& set_point_light_poses(std::vector<glm::vec3> pos);
    ShaderProgram& set_spot_light_poses(std::vector<glm::vec3> pos);
    ShaderProgram& set_spot_light_dirs(std::vector<glm::vec3> pos);
    
    ShaderProgram& set_vec3(std::string uniform_name, glm::vec3 v);
    ShaderProgram& set_float(std::string uniform_name, float f);
    
    std::string get_array_uniform_name(std::string uniform_name, int index);
    std::string get_array_uniform_struct_field_name(std::string uniform_name, std::string field_name, int index);
    
    void check_for_lights_count(std::size_t size);
    
private:
    std::vector<Shader> pipeline;
    GLuint handle = 0;
    
    bool linked = false;
    
    static std::array<std::string, maps_types_count> map_uniform_names;
    
    static const std::string diffuse_map_name;                   // TODO: in future get this from parsing shader or something...
    static const std::string normal_map_name;
    static const std::string specular_map_name;
    static const std::string displacement_map_name;
    static const std::string cubemap_name;
    
    static const std::size_t LIGHTS_COUNT = 0;
    
private:
    
    template<class... Targs>
    void init_pipeline(Shader&& s, Targs&&... args)
    {
        init_pipeline(std::move(s));
        
        init_pipeline(std::forward<Targs>(args)...);
    }
    void init_pipeline(Shader&& s)
    {
        glAttachShader(handle, s.get_handle());
        pipeline.push_back(std::move(s));
    }
    void init_pipeline()
    {
        
    }
};

#endif /* ShaderProgram_hpp */
