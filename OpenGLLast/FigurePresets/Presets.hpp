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
std::vector<float> get_light_cube();
std::vector<float> get_quad();

std::vector<float> get_triangle();

std::vector<glm::vec3> get_positions();

#endif /* Presets_hpp */
