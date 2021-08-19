//
//  Skybox.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 27.05.2021.
//

#ifndef Skybox_hpp
#define Skybox_hpp

#include <iostream>
#include <memory>

#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "ObjectData.hpp"

#include "Cubemap.hpp"

class Skybox
{
public:
    Skybox(ObjectData<float> d);            // TODO: need to store vec3 position (for light)
    
    Skybox(const Skybox& o);
    Skybox& operator=(const Skybox& o);
    
    Skybox(Skybox&& o);
    Skybox& operator=(Skybox&& o);
    
    Skybox& set_cubemap(std::shared_ptr<ITexture> t);
    std::shared_ptr<ITexture> get_cubemap();
    
    VertexArrayObject* get_vao() const;
    VertexBufferObject* get_vbo() const;
    
    ObjectData<float>* get_object_data();
    
    
private:
    std::unique_ptr<VertexArrayObject> vao;
    std::unique_ptr<VertexBufferObject> vbo;
    
    ObjectData<float> object_data;
    
    std::shared_ptr<ITexture> cubemap;
};

#endif /* Skybox_hpp */
