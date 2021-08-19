#version 410

out vec4 FragColor;

in vec3 TexCoord;

uniform samplerCube cubemap;

void main()
{
    vec4 sampled = texture(cubemap, TexCoord);
    //FragColor = vec4(sampled.x, sampled.y, sampled.z, 1.0f);
    //FragColor = vec4(TexCoord.x, TexCoord.y, TexCoord.z, 1.0f);
    //FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

    FragColor = texture(cubemap, TexCoord);
}