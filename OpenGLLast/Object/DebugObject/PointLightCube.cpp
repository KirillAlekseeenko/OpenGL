//
//  PointLightCube.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 08.06.2021.
//

#include "PointLightCube.hpp"

#include "Presets.hpp"

#include "IRenderer.hpp"


PointLightCube::PointLightCube(float size_multiplier)
{
    auto obj_data = ObjectData<float>::create_data();
    
    obj_data
        .set_data(get_light_cube(size_multiplier))
        .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0})
        .set_attribute_pointer(AttributePointer{1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))});
    
    
    cube = std::make_unique<Object>(obj_data);
}

void PointLightCube::draw(IRenderer* renderer, std::shared_ptr<ShaderProgram> shader)
{
    renderer->draw(cube.get(), shader.get());
}

void PointLightCube::set_position(glm::vec3 pos)
{
    cube->set_world_position(pos);
}
