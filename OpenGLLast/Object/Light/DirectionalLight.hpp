//
//  DirectionalLight.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.05.2021.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include <glm/glm.hpp>

#include "ILightSource.hpp"
#include "Vector.hpp"

class DirectionalLight : public ILightSource
{
public:
    
    DirectionalLight(glm::vec3 d);
    
    std::shared_ptr<IDebugObject> get_visual_source() const override;                                     // lamp sun or another object acting as a source
    std::unique_ptr<IShaderLightHalper> get_shader_helper() const override;
    
    LightType get_type() const override;
    
    void set_direction(glm::vec3 d);
    glm::vec3 get_direction() const;
    
    void set_visual_pos(glm::vec3 d);
    glm::vec3 get_visual_pos() const;
private:
    glm::vec3 direction;
    std::shared_ptr<Vector> visual_repr;
    
    glm::vec3 visual_pos;
    
private:
    void check_dir(glm::vec3 d);
    void update_visual_obj();
};

#endif /* DirectionalLight_hpp */
