//
//  DirLightActor.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.06.2021.
//

#ifndef DirLightActor_hpp
#define DirLightActor_hpp

#include "Actor.hpp"
#include "DirectionalLight.hpp"

class DirLightActor : public IActor
{
public:
    DirLightActor(std::shared_ptr<DirectionalLight> dir_light);
    
    void move_offset(glm::vec3 offset) override;
    void rotate_offset(glm::vec3 offset) override;
    
private:
    std::shared_ptr<DirectionalLight> dir_light;
    
    float current_yaw;
    float current_pitch;
    
    static constexpr float pitch_constrain = (float) M_PI_2;
};

#endif /* DirLightActor_hpp */
