//
//  PointLightActor.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 30.06.2021.
//

#ifndef PointLightActor_hpp
#define PointLightActor_hpp

#include "Actor.hpp"

#include "PointLight.hpp"

class PointLightActor : public IActor
{
public:
    
    PointLightActor(std::shared_ptr<PointLight> point_light);
    
    void move_offset(glm::vec3 offset) override;
    void rotate_offset(glm::vec3 offset) override;
    
private:
    
    std::shared_ptr<PointLight> point_light;
};

#endif /* PointLightActor_hpp */
