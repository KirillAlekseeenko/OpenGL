//
//  DeferredRenderer.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.05.2021.
//

#ifndef DeferredRenderer_hpp
#define DeferredRenderer_hpp

#include "IRenderer.hpp"


class DeferredRenderer : public IRenderer
{
public:
    void draw(Object* o, ShaderProgram* shader) override;
    void draw_outlined(Object* o, ShaderProgram *shader, ShaderProgram* outline_shader) override;
    void draw_vector(Vector* v, ShaderProgram* shader) override;
    
    void draw_scene(const Scene& scene) override;
};

#endif /* DeferredRenderer_hpp */
