//
//  IDebugObject.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 08.06.2021.
//

#ifndef IDebugObject_hpp
#define IDebugObject_hpp

#include "ShaderProgram.hpp"
#include <glm/glm.hpp>

class IRenderer;

class IDebugObject
{
public:
    virtual void draw(IRenderer* renderer, std::shared_ptr<ShaderProgram> shader) = 0;
};

#endif /* IDebugObject_hpp */
