//
//  Presets.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.04.2021.
//

#ifndef Presets_hpp
#define Presets_hpp

#include <glm/glm.hpp>

#include <vector>
#include <iostream>

std::vector<float> get_pyramide();
std::vector<float> get_light_cube(float size = 1.0f);
std::vector<float> get_skybox_cube();
std::vector<float> get_quad();

std::vector<float> get_triangle();

std::vector<glm::vec3> get_positions();

std::vector<float> get_earth_plane(float size = 1.0f);

#endif /* Presets_hpp */
