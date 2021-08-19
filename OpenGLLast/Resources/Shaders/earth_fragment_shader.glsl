#version 410

out vec4 FragColor;

in vec2 texCoords;

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;                    
uniform sampler2D specular_map;                   
uniform sampler2D disp_map;

void main()
{
    FragColor = texture(diffuse_map, texCoords);
}