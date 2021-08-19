#version 410

layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 projection; 
uniform mat4 view;  

out vec3 TexCoord;

void main()
{
    TexCoord = pos;                                                       // assume that cube is in the center, so pos means direction
    mat4 cubemap_view = mat4(mat3(view));                                  // remove translation component
    vec4 screen_pos = projection * cubemap_view * vec4(pos, 1.0f);
    gl_Position = screen_pos.xyww;                                         // set z to w, to get 1.0f depth
}