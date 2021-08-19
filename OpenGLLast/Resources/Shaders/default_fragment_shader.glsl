#version 410

#define LIGHT_AMOUNT 1                  // think of a more sophisticated way...

in vec3 fragColor;
in vec2 textCoords;
in vec3 fragNormal;   
in vec3 fragTangent;
in vec3 fragBTangent;                                 // normal calculated from triangles

in vec3 fragPos;
in vec3 fragViewPos;

// misc prmtrs

uniform float ambientStrength;
uniform float height_scale;

// maps

uniform sampler2D diffuse_map;
uniform sampler2D normal_map;                     // normals
uniform sampler2D specular_map;                   // specular intensity
uniform sampler2D disp_map;

// light sources

in vec3 dirLightFragDir[LIGHT_AMOUNT];
in vec3 pointLightFragPos[LIGHT_AMOUNT];
in vec3 spotLightFragPos[LIGHT_AMOUNT];
in vec3 spotLightFragDir[LIGHT_AMOUNT];

struct PointLight
{
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
};

uniform PointLight pointLights[LIGHT_AMOUNT];
uniform SpotLight spotLights[LIGHT_AMOUNT];

//

out vec4 FragColor;

vec2 get_displaced_tex_coords(vec2 origin, vec3 fragPosToView);
bool is_in_range(vec2 t_coords);

vec4 get_frag_color(vec4 diffuse, vec3 specular, vec3 normal_vector, vec3 fragPosToView, vec3 fragPosToLight);

vec4 get_dir_light_color(vec4 diffuse, vec3 specular, vec3 normal_vector, int arr_index);
vec4 get_point_light_color(vec4 diffuse, vec3 specular, vec3 normal_vector, int arr_index);
//vec4 get_spot_light_color(vec4 diffuse, vec3 specular, vec3 normal_vector, int arr_index);

void main()
{
    vec2 diplaced_tex_coords = textCoords;// get_displaced_tex_coords(textCoords, fragPosToView);       // parallax

    //if (!is_in_range(diplaced_tex_coords)) discard;                                        // parallax

    vec3 normFragToView = normalize(fragViewPos - fragPos);
    //vec3 normFragToLight = normalize(fragLightPos - fragPos);

    vec4 diffuse_color = texture(diffuse_map, diplaced_tex_coords);
    vec4 normal_color = texture(normal_map, diplaced_tex_coords);
    vec4 sampled_specular_color = texture(specular_map, diplaced_tex_coords);

    vec3 normal_vector = vec3(normalize(normal_color * 2.0f - 1.0f));

    vec4 color = vec4(0.0f);

    for (int i = 0; i < LIGHT_AMOUNT; i++)
    {
        color += get_dir_light_color(diffuse_color, vec3(0.0f, 0.0f, 0.0f), normal_vector, i);
    }

    for (int i = 0; i < LIGHT_AMOUNT; i++)
    {
        color += get_point_light_color(diffuse_color, vec3(0.0f, 0.0f, 0.0f), normal_vector, i);
    }
    
    FragColor = vec4(vec3(color), 1.0f); //get_frag_color(diffuse_color, vec3(0.0f, 0.0f, 0.0f), normal_vector, normFragToView, normFragToLight);
}

vec4 get_frag_color(vec4 diffuse, vec3 specular, vec3 normal_vector, vec3 fragPosToView, vec3 fragPosToLight)   // blihn-phong method
{
    vec3 halfway = normalize(fragPosToView + fragPosToLight);

    float diffusePower = max(dot(normal_vector, fragPosToLight), 0.0f);

    float specularCut = ceil(dot(fragPosToLight, vec3(0.0f, 0.0f, 1.0f)));
    float diffuseCut = min(max(dot(fragPosToLight, vec3(0.0f, 0.0f, 1.0f)), 0.0f) * 3.0f, 1.0f);

    diffusePower *= diffuseCut;         
    float specularColor = pow(max(dot(halfway, normal_vector), 0.0f), 32.0f) * specularCut;

    return diffuse * (diffusePower + ambientStrength + specularColor);
}

vec4 get_dir_light_color(vec4 diffuse, vec3 specular, vec3 normal_vector, int arr_index)
{
    vec3 lightDir = dirLightFragDir[arr_index];

    vec3 normFragToView = normalize(fragViewPos - fragPos);
    vec3 normFragToLight = normalize(-lightDir);

    return get_frag_color(diffuse, specular, normal_vector, normFragToView, normFragToLight);
}

vec4 get_point_light_color(vec4 diffuse, vec3 specular, vec3 normal_vector, int arr_index)
{
    float constant = pointLights[arr_index].constant;
    float linear = pointLights[arr_index].linear;
    float quadratic = pointLights[arr_index].quadratic;

    vec3 lightPos = pointLightFragPos[arr_index];

    vec3 normFragToLight = normalize(lightPos - fragPos);
    vec3 normFragToView = normalize(fragViewPos - fragPos);

    float dst = length(lightPos - fragPos);
    float attenuation = 1.0f / (constant + dst * linear + pow(dst, 2.0f) * quadratic);

    //vec3 z_normal = vec3(0.0f, 0.0f, 1.0f);

    return vec4(vec3(get_frag_color(diffuse, specular, normal_vector, normFragToView, normFragToLight)) * attenuation, 1.0f);
    //return vec4(max(dot(normFragToLight, z_normal), 0.0f), 0.0f, 0.0f, 1.0f);

    //return vec4(constant, 0.0f, 0.0f, 1.0f);
}

/*

vec4 get_spot_light_color(vec4 diffuse, vec3 specular, vec3 normal_vector, int arr_index)
{
    float constant = spotLights[arr_index].constant;
    float linear = spotLights[arr_index].linear;
    float quadratic = spotLights[arr_index].quadratic;

    float cutOff = spotLights[arr_index].cutOff;                                 // dot() < outerCutOff <=> no light
    float outerCutOff = spotLights[arr_index].outerCutOff;

    vec3 lightPos = spotLightFragPos[arr_index];
    vec3 lightDir = normalize(spotLightFragDir[arr_index]);

    //

    vec3 normFragToLight = normalize(lightPos - fragPos);
    vec3 normFragToView = normalize(fragViewPos - fragPos);

    vec3 frag_color = vec3(get_frag_color(diffuse, specular, normal_vector, normFragToView, normFragToLight));

    float dst = length(lightPos - fragPos);
    float attenuation = 1.0f / (constant + dst * linear + pow(dst, 2.0f) * quadratic);

    float fragDirDot = max(dot(lightDir, -normFragToLight), 0.0f);                                        // for simplicity cutoff angle shoudnt be higher than pi

    float intensity_inner = ceil(fragDirDot - cutOff);
    float intensity_border = ceil(cutOff - fragDirDot) * max(fragDirDot - cutOff, 0.0f) / (cutOff - outerCutOff);

    float intensity = intensity_inner + intensity_border;

    return vec4(frag_color * attenuation * intensity, 1.0f);
}

*/

// TODO: try to add shadows
vec2 get_displaced_tex_coords(vec2 origin, vec3 fragPosToView)             
{
    
    float depth = texture(disp_map, origin).r;                                            // we need to find displaced texture coords
    vec2 p = fragPosToView.xy / fragPosToView.z * (depth * height_scale);
    //return textCoords - p;

    const float min_layers_amount = 2.0f;
    const float max_layers_amount = 6.0f;
    float opt_layers_amount = ceil(mix(max_layers_amount, min_layers_amount, max(dot(fragPosToView, vec3(0.0f, 0.0f, 1.0f)), 0.0f)));

    float layer_depth = 1.0f / opt_layers_amount;

    // need to implement steep parallax with lerp

    vec2 full_depth_offset = fragPosToView.xy / fragPosToView.z * (height_scale);
    vec2 layer_offset = full_depth_offset / opt_layers_amount;

    vec2 currentCoords = origin;
    float current_layer_depth = 0.0f;
    float current_depth = texture(disp_map, currentCoords).r;

    float prev_layer_depth = current_layer_depth;
    float prev_depth = current_depth;

    int cycles = 0;

    while (current_depth > current_layer_depth)
    {
        currentCoords -= layer_offset;

        prev_layer_depth = current_layer_depth;
        prev_depth = current_depth;

        current_layer_depth += layer_depth;
        current_depth = texture(disp_map, currentCoords).r;

        cycles++;
    }

    bool use_lerp = false;

    if (use_lerp) return origin - full_depth_offset * current_depth;

    // lerp

    float x1 = prev_depth - prev_layer_depth;
    float y1 = prev_depth;

    float x0 = current_depth - current_layer_depth;
    float y0 = current_depth;

    float x = 0;

    float w = (x - x0) / (x1 - x0);

    float lerped_depth = y0 * (1 - w) + y1 * w;

    return origin - full_depth_offset * lerped_depth;
}

bool is_in_range(vec2 t_coords)
{
    return t_coords.x >= 0.0f && t_coords.x <= 1.0f && t_coords.y >= 0.0f && t_coords.y <= 1.0f; 
}

