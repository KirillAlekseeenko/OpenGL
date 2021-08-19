#version 410

// flinh-phong model

#define LIGHT_AMOUNT 1

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 normal;
layout (location = 4) in vec3 tangent; 
layout (location = 5) in vec3 bTangent;              // we can omit bTangent here and calculate it by making cross product with normal and tangent  

uniform mat4 model;
uniform mat4 projection; 
uniform mat4 view;  

uniform vec3 lightPos;                // make array of light in future; dont know how to kind of normalize color, if too much light is lit on surface      
uniform vec3 viewPos;

out vec3 fragColor;
out vec2 textCoords;
out vec3 fragNormal;

out vec3 fragPos;
out vec3 fragViewPos;

//out vec3 fragPosToView;
//out vec3 fragPosToLight;

out vec3 fragTangent;
out vec3 fragBTangent;



// light sources

uniform vec3 dirLightDir[LIGHT_AMOUNT];
uniform vec3 pointLightPos[LIGHT_AMOUNT];
uniform vec3 spotLightPos[LIGHT_AMOUNT];
uniform vec3 spotLightDir[LIGHT_AMOUNT];

out vec3 dirLightFragDir[LIGHT_AMOUNT];
out vec3 pointLightFragPos[LIGHT_AMOUNT];
out vec3 spotLightFragPos[LIGHT_AMOUNT];
out vec3 spotLightFragDir[LIGHT_AMOUNT];

void process_light_sources(mat3 tbnMatrix);

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0f);
    fragColor = color;

    mat3 normalMatrix = mat3(transpose(inverse(model)));

    fragNormal = normalize(normalMatrix * normal);
    fragTangent = normalize(normalMatrix * tangent);
    fragBTangent = normalize(normalMatrix * bTangent);
    
    textCoords = texCoords;

    mat3 tbnMatrix = mat3(fragTangent, fragBTangent, fragNormal);

    mat3 transposedTBNMatrix = transpose(tbnMatrix);  

    vec3 vtxPos = vec3(model * vec4(pos, 1.0f));

    fragPos = transposedTBNMatrix * vtxPos;
    fragViewPos = transposedTBNMatrix * viewPos;

    // process light sources

    process_light_sources(transposedTBNMatrix);
}

void process_light_sources(mat3 tbnMatrix)
{
    for (int i = 0; i < LIGHT_AMOUNT; i++)
    {
        dirLightFragDir[i] = tbnMatrix * normalize(dirLightDir[i]);
        spotLightFragDir[i] = tbnMatrix * normalize(spotLightDir[i]);

        pointLightFragPos[i] = tbnMatrix * pointLightPos[i];
        spotLightFragPos[i] = tbnMatrix * spotLightPos[i];
        
    }
}