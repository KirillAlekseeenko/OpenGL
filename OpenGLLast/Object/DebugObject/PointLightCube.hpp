//
//  PointLightCube.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 08.06.2021.
//

#ifndef PointLightCube_hpp
#define PointLightCube_hpp

#include "IDebugObject.hpp"

#include "Object.hpp"

class PointLightCube : public IDebugObject
{
public:
    PointLightCube(float size_multiplier);
    
    void draw(IRenderer* renderer, std::shared_ptr<ShaderProgram> shader) override;
    void set_position(glm::vec3 pos);
private:
    std::unique_ptr<Object> cube;
};

#endif /* PointLightCube_hpp */
