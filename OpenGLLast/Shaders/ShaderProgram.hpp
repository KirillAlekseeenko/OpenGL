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
private:
    std::vector<Shader> pipeline;
    GLuint handle = 0;
    
    bool linked = false;
    
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
