//
//  Presets.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 16.04.2021.
//

#include "Presets.hpp"

std::vector<float> get_pyramide()
{
    /*return std::vector<float>{
        // quad basement
        0.0f, 0.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,                 // TODO: model center should be in (0, 0, 0)
        0.0f, 1.0f, 0.0f,       0.5f, 0.2f, 0.2f,     0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,       0.5f, 0.2f, 0.2f,      1.0f, 0.0f,
        
        1.0f, 0.0f, 0.0f,       0.5f, 0.2f, 0.2f,      1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,       0.5f, 0.2f, 0.2f,      1.0f, 1.0f,
        
        // triangles
        
        0.5f, 0.5f, 1.0f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        0.0f, 1.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        
        0.0f, 0.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        1.0f, 0.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        0.5f, 0.5f, 1.0f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        
        1.0f, 0.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        1.0f, 1.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.5f, 0.5f, 1.0f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        
        1.0f, 1.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.5f, 0.5f, 1.0f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        
    };*/
    
    /*return std::vector<float>{
        -0.5f, -0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,                 // small bias in basement
        -0.5f, 0.5f, -0.5f,       0.5f, 0.2f, 0.2f,     0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      1.0f, 0.0f,
        
        0.5f, -0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.0f, 1.0f,
        0.5f, 0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      1.0f, 1.0f,
        
        // triangles
        
        0.0f, 0.0f, 0.5f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        -0.5f, 0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.5f, -0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        0.0f, 0.0f, 0.5f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        
        0.5f, -0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        
        0.5f, 0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.0f, 0.0f, 0.5f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
    };*/
    
    return std::vector<float>{
        -0.5f, -0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        -0.5f, 0.5f, -0.3f,       0.5f, 0.2f, 0.2f,     0.0f, 1.0f,
        0.5f, -0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      1.0f, 0.0f,
        
        0.5f, -0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      1.0f, 0.0f,
        -0.5f, 0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.0f, 1.0f,
        0.5f, 0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      1.0f, 1.0f,
        
        // triangles
        
        0.0f, 0.0f, 0.7f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        -0.5f, 0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        -0.5f, -0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        
        -0.5f, -0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.5f, -0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        0.0f, 0.0f, 0.7f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        
        0.5f, -0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        0.5f, 0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.0f, 0.0f, 0.7f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
        
        0.5f, 0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.0f, 0.0f,
        -0.5f, 0.5f, -0.3f,       0.5f, 0.2f, 0.2f,      0.5f, 0.0f,
        0.0f, 0.0f, 0.7f,       0.5f, 0.2f, 0.2f,      0.25f, 0.56f,
    };
}

std::vector<float> get_triangle()
{
    return std::vector<float>{
             // first triangle
             -0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.3f,      0.0f, 0.0f,
             0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.3f,      1.0f, 0.0f,
             0.0f, 0.5f, 0.0f,       0.0f, 1.0f, 0.3f,      0.5f, 1.0f
    };
}

std::vector<glm::vec3> get_positions()
{
    return std::vector<glm::vec3>
    {
        glm::vec3( 0.0f,  0.0f,  0.0f),
                glm::vec3( 2.0f,  5.0f, -15.0f),
                glm::vec3(-1.5f, -2.2f, -2.5f),
                glm::vec3(-3.8f, -2.0f, -12.3f),
                glm::vec3( 2.4f, -0.4f, -3.5f),
                glm::vec3(-1.7f,  3.0f, -7.5f),
                glm::vec3( 1.3f, -2.0f, -2.5f),
                glm::vec3( 1.5f,  2.0f, -2.5f),
                glm::vec3( 1.5f,  0.2f, -1.5f),
                glm::vec3(-1.3f,  1.0f, -1.5f)
    };
}

std::vector<float> get_light_cube(float size)
{
    std::vector<float> data{
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // Bottom-left
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-right
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-right
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-left
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
            // Front face
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // top-right
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // top-right
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // top-left
            // Left face
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // top-right
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-left
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // top-right
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
            // Right face
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // top-left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-right
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // top-left
            // Bottom face
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  // top-right
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-left
             0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
            -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-right
            -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
            // Top face
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-left
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-right
            -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,   // bottom-left
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,   // top-left
    };
    
    for (auto i = 0; i < data.size(); i++)
    {
        if (i % 6 >= 3) continue;
        
        data[i] *= size;
    }
    
    return data;
}

std::vector<float> get_skybox_cube()
{
    return std::vector<float>{
        -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f, -1.0f,
                 1.0f,  1.0f,  1.0f,
                 1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f, -1.0f,
                 1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                 1.0f, -1.0f,  1.0f
    };
}

std::vector<float> get_quad()                 // for framebuffers
{
    return std::vector<float>{};
}

std::vector<float> get_earth_plane(float size)
{
    auto res = std::vector<float>{
        -4.0f, 0.0f,  4.0f,     0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
         4.0f, 0.0f, -4.0f,     1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
        -4.0f, 0.0f, -4.0f,     0.0f, 0.0f, 1.0f,       0.0f, 1.0f,
        
        -4.0f, 0.0f,  4.0f,     0.0f, 1.0f, 0.0f,       0.0f, 0.0f,
         4.0f, 0.0f,  4.0f,     0.0f, 0.0f, 1.0f,       1.0f, 0.0f,
         4.0f, 0.0f, -4.0f,     1.0f, 0.0f, 0.0f,       1.0f, 1.0f,
    };
    
    std::transform(res.begin(), res.end(), res.begin(), [size](float c) {return c * size;});
    
    return res;
}



