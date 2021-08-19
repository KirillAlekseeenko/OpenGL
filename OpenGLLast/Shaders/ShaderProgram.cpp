//
//  ShaderProgram.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#include "ShaderProgram.hpp"
#include <glm/gtc/type_ptr.hpp>

#include <sstream>

#include "Meta.hpp"

ShaderProgram::ShaderProgram(ShaderProgram&& s)
{
    handle = s.handle;
    s.handle = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& s)
{
    if (handle != s.handle)
    {
        for (const auto& c : pipeline)
        {
            glDetachShader(handle, c.get_handle());
        }
        
        glDeleteProgram(handle);
    }
    
    handle = s.handle;
    s.handle = 0;
    
    return *this;
}

ShaderProgram::~ShaderProgram()
{
    if (handle == 0) return;
    
    for (const auto& c : pipeline)
    {
        glDetachShader(handle, c.get_handle());
    }
    
    glDeleteProgram(handle);
}

std::pair<GLint, std::basic_string<GLchar>> ShaderProgram::link()
{
    for (auto& c : pipeline)
    {
        if (!c.is_compiled())
        {
            auto compile_result = c.compile();
            if (std::get<0>(compile_result) == GL_FALSE)
            {
                return compile_result;
            }
        }
    }
    
    glLinkProgram(handle);
    
    GLint link_status = 0;
    glGetProgramiv(handle, GL_LINK_STATUS, &link_status);
    
    std::basic_string<GLchar> log_str;
    
    if (link_status == GL_FALSE)
    {
        GLint log_size = 0;
        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_size);
        
        std::vector<GLchar> log(log_size);
        
        glGetProgramInfoLog(handle, log_size, &log_size, log.data());
        
        std::copy(log.begin(), log.end(), std::back_inserter(log_str));
        
        std::cout << "\nShader compile error: \n" << log_str << "\n";
    }
    else
    {
        linked = true;
    }
    
    return std::pair<GLint, std::basic_string<GLchar>>{link_status, log_str};
}

GLint ShaderProgram::get_uniform_location(std::string name) const
{
    return glGetUniformLocation(handle, name.c_str());
}

bool ShaderProgram::use()
{
    if (!linked) return false;
    
    glUseProgram(handle);
    
    return true;
}

ShaderProgram& ShaderProgram::set_projection_mat(glm::mat4 m)
{
    auto proj_mat_handle = get_uniform_location("projection");
    glUniformMatrix4fv(proj_mat_handle, 1, GL_FALSE, glm::value_ptr(m));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_view_mat(glm::mat4 m)
{
    auto view_mat_handle = get_uniform_location("view");
    glUniformMatrix4fv(view_mat_handle, 1, GL_FALSE, glm::value_ptr(m));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_camera_pos(glm::vec3 p)
{
    auto camera_position = get_uniform_location("viewPos");
    glUniform3fv(camera_position, 1, glm::value_ptr(p));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_light_pos(glm::vec3 p)
{
    auto light_position = get_uniform_location("lightPos");
    glUniform3fv(light_position, 1, glm::value_ptr(p));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_ambient_strength(float s)
{
    auto ambient_strength = get_uniform_location("ambientStrength");
    glUniform1f(ambient_strength, s);
    
    return *this;
}

ShaderProgram& ShaderProgram::set_outline_color(glm::vec3 v)
{
    auto outline_color = get_uniform_location("outline_color");
    glUniform3fv(outline_color, 1, glm::value_ptr(v));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_map_uniform(TextureType type)
{
    auto index = to_underlying(type);
    auto& uniform_name = map_uniform_names[index];
    auto uniform_location = get_uniform_location(uniform_name);
    
    glUniform1i(uniform_location, static_cast<int>(index));
    
    return *this;
}


ShaderProgram& ShaderProgram::set_height_scale(float s)
{
    auto height_scale = get_uniform_location("height_scale");
    glUniform1f(height_scale, s);
    
    return *this;
}

ShaderProgram& ShaderProgram::set_dir_light_direction(glm::vec3 d)
{
    auto uniform = get_uniform_location("dirLightDir");
    glUniform3f(uniform, d.x, d.y, d.z);
    
    return *this;
}

ShaderProgram& ShaderProgram::set_point_light_poses(std::vector<glm::vec3> pos)
{
    if (pos.size() == 0) return *this;
    
    check_for_lights_count(pos.size());
    
    auto uniform = get_uniform_location("pointLightPos");
    glUniform3fv(uniform, static_cast<GLsizei>(pos.size()), glm::value_ptr(pos[0]));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_spot_light_poses(std::vector<glm::vec3> pos)
{
    if (pos.size() == 0) return *this;
    
    check_for_lights_count(pos.size());
    
    auto uniform = get_uniform_location("spotLightPos");
    glUniform3fv(uniform, static_cast<GLsizei>(pos.size()), glm::value_ptr(pos[0]));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_spot_light_dirs(std::vector<glm::vec3> ds)
{
    if (ds.size() == 0) return *this;
    
    check_for_lights_count(ds.size());
    
    auto uniform = get_uniform_location("spotLightDir");
    glUniform3fv(uniform, static_cast<GLsizei>(ds.size()), glm::value_ptr(ds[0]));
    
    return *this;
}

ShaderProgram& ShaderProgram::set_vec3(std::string uniform_name, glm::vec3 v)
{
    auto uniform = get_uniform_location(uniform_name);
    glUniform3f(uniform, v.x, v.y, v.z);
    
    return *this;
}

ShaderProgram& ShaderProgram::set_float(std::string uniform_name, float f)
{
    auto uniform = get_uniform_location(uniform_name);
    glUniform1f(uniform, f);
    
    return *this;
}

std::string ShaderProgram::get_array_uniform_name(std::string uniform_name, int index)
{
    auto array_name = std::stringstream{};
    
    array_name << uniform_name;
    array_name << '[' << index << ']';
    
    return array_name.str();
}

std::string ShaderProgram::get_array_uniform_struct_field_name(std::string uniform_name, std::string field_name, int index)
{
    auto array_name = std::stringstream{};
    
    array_name << uniform_name;
    array_name << '[' << index << ']';
    array_name << '.' << field_name;
    
    return array_name.str();
}

void ShaderProgram::check_for_lights_count(std::size_t size)
{
    if (size != LIGHTS_COUNT) throw std::runtime_error("Light sources count is invalid");
}

const std::string ShaderProgram::diffuse_map_name = "diffuse_map";                   // TODO: in future get this from parsing shader or something...
const std::string ShaderProgram::normal_map_name = "normal_map";
const std::string ShaderProgram::specular_map_name = "specular_map";
const std::string ShaderProgram::displacement_map_name = "disp_map";
const std::string ShaderProgram::cubemap_name = "cubemap";

std::array<std::string, maps_types_count> ShaderProgram::map_uniform_names = std::array<std::string, maps_types_count>
{
    diffuse_map_name,
    normal_map_name,
    specular_map_name,
    displacement_map_name,
    cubemap_name
};

std::unique_ptr<ShaderProgram> ShaderProgram::create_shader(Dir dir, std::string vertex_local_path, std::string fragment_local_path)
{
    return create_shader(dir.get_relative_path(vertex_local_path), dir.get_relative_path(fragment_local_path));
}

std::unique_ptr<ShaderProgram> ShaderProgram::create_shader(std::string vertex_abs_path, std::string fragment_abs_path)
{
    return std::make_unique<ShaderProgram>(Shader(GL_VERTEX_SHADER, vertex_abs_path), Shader(GL_FRAGMENT_SHADER, fragment_abs_path));
}
