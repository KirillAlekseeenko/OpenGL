//
//  Object.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 13.04.2021.
//

#ifndef Object_hpp
#define Object_hpp

#include "ShaderProgram.hpp"
#include "VertexBufferObject.hpp"
#include "VertexArrayObject.hpp"
#include "Texture.hpp"
#include "TextureType.hpp"
#include "ObjectData.hpp"
#include "Camera.hpp"

#include "AuxiliaryTexture.hpp"

#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <array>

#include "Actor.hpp"

#include "IDObj.hpp"

#include "DrawParameters.hpp"

class Object : public IActor, public IDObj
{
    using maps_arr = std::array<std::shared_ptr<ITexture>, maps_types_count>;
    
public:
    Object(ObjectData<float> d);            // TODO: need to store vec3 position (for light)
    
    Object(const Object& o);
    Object& operator=(const Object& o);
    
    Object(Object&& o);
    Object& operator=(Object&& o);
    
    Object& edit_vbo(std::function<void(VertexBufferObject* vbo)>);
    
    Object& translate(glm::vec3 v);
    Object& set_world_position(glm::vec3 v);
    Object& rotate(float angle, glm::vec3 axis);
    Object& scale(glm::vec3 s);
    
    glm::mat4 get_position();
    glm::vec3 get_world_position();
    
    Object& set_diffuse(std::shared_ptr<ITexture> t);
    std::shared_ptr<ITexture> get_diffuse();
    
    Object& set_normal_map(std::shared_ptr<ITexture> t);
    std::shared_ptr<ITexture> get_normal_map();
    
    Object& set_specular_map(std::shared_ptr<ITexture> t);
    std::shared_ptr<ITexture> get_specular_map();
    
    Object& set_disp_map(std::shared_ptr<ITexture> t);
    std::shared_ptr<ITexture> get_disp_map();
    
    maps_arr& get_all_maps();
    
    void move_offset(glm::vec3 offset) override;
    void rotate_offset(glm::vec3 offset) override;
    
    DrawParameters& get_draw_parameters();
    
    VertexArrayObject* get_vao() const;
    VertexBufferObject* get_vbo() const;
    
    ObjectData<float>* get_object_data();
    
    static std::shared_ptr<Object> create_dir_light_obj();
    
private:
    std::unique_ptr<VertexArrayObject> vao;
    std::unique_ptr<VertexBufferObject> vbo;
    
    glm::mat4 translation_matrix {1.0f};
    glm::mat4 scale_matrix {1.0f};
    glm::mat4 rotation_matrix {1.0f};
    
    glm::vec3 world_position {0.0f, 0.0f, 0.0f};
    
    ObjectData<float> object_data;
    maps_arr maps;
    
    Object& set_texture(std::shared_ptr<ITexture> &&t, TextureType type);
    std::shared_ptr<ITexture> get_texture(TextureType type);
    
    
    // RUNTIME PROPS
    
    bool is_ready_for_drawing = false;
    
    GLint model_uniform = 0;
    GLint texture_uniform = 0;
    
    DrawParameters draw_parameters;
    
};

#endif /* Object_hpp */
