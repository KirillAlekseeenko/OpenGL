//
//  ForwardRenderer.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.05.2021.
//

#ifndef ForwardRenderer_hpp
#define ForwardRenderer_hpp

#include "IRenderer.hpp"
#include "Skybox.hpp"

class ForwardRenderer : public IRenderer
{
public:
    void draw(Object* o, ShaderProgram* shader) override;
    void draw_vector(Vector* v, ShaderProgram* shader) override;
    
    void draw_outlined(Object* o, ShaderProgram *shader, ShaderProgram* outline_shader) override;
    
    void draw_scene(const Scene& scene) override;
    
private:
    void __drawObject(Object* o, ShaderProgram* shader, ShaderProgram* outline_shader = nullptr);
    void __drawSkybox(Skybox* skybox, ShaderProgram* skybox_shader);
    
    void __getShadowMap(ShaderProgram* shadowMapShader);
    
private:
    
};

#endif /* ForwardRenderer_hpp */
