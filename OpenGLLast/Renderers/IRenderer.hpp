//
//  IRenderer.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.05.2021.
//

#ifndef IRenderer_hpp
#define IRenderer_hpp

class ShaderProgram;
class Vector;
class Object;
class Scene;

class IRenderer
{
public:
    virtual void draw(Object* o, ShaderProgram* shader) = 0;
    virtual void draw_vector(Vector* v, ShaderProgram* shader) = 0;
    virtual void draw_outlined(Object* o, ShaderProgram *shader, ShaderProgram* outline_shader) = 0;
    
    virtual void draw_scene(const Scene& scene) = 0;
protected:
    int shadow_maps_cascades_count = 3;
};

#endif /* IRenderer_hpp */
