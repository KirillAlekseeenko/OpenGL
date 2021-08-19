//
//  main.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 10.04.2021.
//

#define GL_SILENCE_DEPRECATION

#include "SimpleRenderer.hpp"
#include "IRenderer.hpp"
#include "ForwardRenderer.hpp"

#include "DirectionalLight.hpp"

#include "DirLightActor.hpp"
#include "PointLightActor.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
int lib_init(GLFWwindow* &window);
void forward_render(GLFWwindow* window);
void clean_up();

int main()
{
    GLFWwindow* window = nullptr;
    auto r = lib_init(window);
    
    if (r != 0 || window == nullptr)
    {
        clean_up();
        return r;
    }
    
    try
    {
        forward_render(window);
    }
    catch(...)
    {
        clean_up();
    }
    
    clean_up();
    
    return 0;
}

int lib_init(GLFWwindow* &w)
{
    GLFWwindow* window;
    
    if(!glfwInit())
        return -1;

    // Initialize the library
    // Define version and compatibility settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    // Create a windowed mode window and its OpenGL context
    // GLFWmonitor is needed if you want to make full screen window (if you do, supply this function with your primary monitor)
    // GLFWwindow is needed to set window that will share the context created by this function (see Context Object Sharing)
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        const char* description;
        auto code = glfwGetError(&description);
        std::cout << "Error code: " << code << std::endl;
        std::cout << "Description: " << description << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Mathe the window's context current
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    auto err = glewInit();
    
    if (err != GLEW_OK)
    {
        std::cout << "\nGLEW initialization failed, error code: " << err << ", description: " << glewGetErrorString(err) << "\n";
        return -1;
    }
    
    w = window;
    
    return 0;
}

/* 1. create shader collection class, that will link them, and set camera, lights etc
   2. think of a way to transform normal vectors according to the position of object
   3. track object location, rotation i.e. transform (now location is wrong when object (out only light) is scaled
   4. inputs collection, maybe we should create new class
   5. attach objects to shader the use, it allow to draw all objects in a single for loop
   6. somehow simplify object creation*/

void forward_render(GLFWwindow* window)
{
    auto renderer = new ForwardRenderer();
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0x00);
    
    glPointSize(20.0f);
    
    glFrontFace(GL_CCW);
    
    InputController input_controller;
    
    auto camera = std::make_shared<Camera>();
    camera->set_postion(glm::vec3(0.0f, 0.0f, 2.0f));
    
    std::vector<std::shared_ptr<ShaderProgram>> all_shaders;
    std::vector<std::shared_ptr<ITexture>> all_textures;
    
    Dir shaders_dir {"/Users/kirillalekseenko/Documents/cpptrain/OpenGLLast/OpenGLLast/Resources/Shaders/"};
    Dir textures_dir {"/Users/kirillalekseenko/Documents/cpptrain/OpenGLLast/OpenGLLast/Resources/Textures/"};
    

    
    auto default_shader = static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::create_shader(shaders_dir,
                                                                                                   "default_vertex_shader.glsl",
                                                                                                   "default_fragment_shader.glsl"));
    
    auto light_shader = static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::create_shader(shaders_dir,
                                                                                                   "light_vertex_shader.glsl",
                                                                                                   "light_fragment_shader.glsl"));
    
    auto outline_shader = static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::create_shader(shaders_dir,
                                                                                                   "outlined_vertex_shader.glsl",
                                                                                                   "outlined_fragment_shader.glsl"));
    auto skybox_shader = static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::create_shader(shaders_dir,
                                                                                                  "skybox_vertex_shader.glsl",
                                                                                                  "skybox_fragment_shader.glsl"));
    
    auto earth_shader = static_cast<std::shared_ptr<ShaderProgram>>(ShaderProgram::create_shader(shaders_dir,
                                                                                                  "earth_vertex_shader.glsl",
                                                                                                  "earth_fragment_shader.glsl"));
    
    Scene scene (default_shader, camera, light_shader, outline_shader);
    
    
    all_shaders.push_back(light_shader);
    all_shaders.push_back(default_shader);
    all_shaders.push_back(outline_shader);
    all_shaders.push_back(skybox_shader);
    all_shaders.push_back(earth_shader);
    
    for (auto p : all_shaders)
    {
        auto result = p->link();
        if (std::get<0>(result) == GL_FALSE)
        {
            return;
        }
    }
    
    auto brickwall_duffuse = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "brickwall.jpg"));
    auto brickwall_normal = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "brickwall_normal.jpg"));
    auto brickwall_spec = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "brickwall_spec.jpg"));
    
    auto toy_diffuse = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "toy_box_diffuse.png"));
    auto toy_normal = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "toy_box_normal.png"));
    auto toy_disp = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "toy_box_disp.png"));
    
    toy_diffuse->set_min_filter(GL_NEAREST);
    toy_normal->set_min_filter(GL_NEAREST);
    toy_disp->set_min_filter(GL_NEAREST);
    //toy_disp->set_mag_filter(GL_LINEAR);
    
    auto bricks2_diffuse = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "bricks2_diffuse.jpg"));
    auto bricks2_normal = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "bricks2_normal.jpg"));
    auto bricks2_disp = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "bricks2_disp.jpg"));
    
    auto cubemap = static_cast<std::shared_ptr<ITexture>>(Cubemap::create_cubemap(textures_dir, std::array<std::string, 6>
                                                                                 {
                                                                                     "skybox_right.jpg",
                                                                                     "skybox_left.jpg",
                                                                                     "skybox_top.jpg",
                                                                                     "skybox_bottom.jpg",
                                                                                     "skybox_front.jpg",
                                                                                     "skybox_back.jpg",
                                                                                 }));
    
    auto earth_diffuse = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "gravel_01_diffuse.jpg"));
    auto earth_normal = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "gravel_01_normal.jpg"));
    auto earth_disp = static_cast<std::shared_ptr<ITexture>>(Texture::create_texture(textures_dir, "gravel_01_height.jpg"));
    
    std::vector<std::shared_ptr<ITexture>> earth_txts {earth_diffuse, earth_normal, earth_disp};
    
    for (auto earth_txt : earth_txts)
    {
        earth_txt->set_wrap_s(GL_REPEAT);
        earth_txt->set_wrap_t(GL_REPEAT);
        earth_txt->set_min_filter(GL_NEAREST);
    }
    
    all_textures.push_back(brickwall_duffuse);             // TODO: create texture unpacker or something...
    all_textures.push_back(brickwall_normal);
    all_textures.push_back(brickwall_spec);
    
    all_textures.push_back(toy_diffuse);
    all_textures.push_back(toy_normal);
    all_textures.push_back(toy_disp);
    
    all_textures.push_back(bricks2_diffuse);
    all_textures.push_back(bricks2_normal);
    all_textures.push_back(bricks2_disp);
    
    all_textures.insert(all_textures.end(), earth_txts.begin(), earth_txts.end());
    
    all_textures.push_back(cubemap);
    
    for (auto t : all_textures)
    {
        if (!t->is_valid())
        {
            std::cout << "\n" << t->get_name() << " texture is invalid";
        }
        else
        {
            t->load_to_vram();
        }
    }
    
    //earth
    
    auto earth_data = ObjectData<float>::create_data().set_data(get_earth_plane())
    .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0})
    .set_attribute_pointer(AttributePointer{1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))})
    .set_attribute_pointer(AttributePointer{2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))});
    
    earth_data.compute_and_add_normals_and_tangents();
    
    auto earth_obj = std::make_shared<Object>(earth_data);
    
    earth_obj->translate(glm::vec3(0.0f, -1.0f, 0.0f));
    
    earth_obj->set_diffuse(earth_diffuse);
    earth_obj->set_normal_map(earth_normal);
    earth_obj->set_disp_map(earth_disp);
    
    
    
    //-------------------------------
    
    // skybox
    
    auto skybox_data = ObjectData<float>{};
    skybox_data.set_data(get_skybox_cube())
    .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0});
    
    auto skybox = std::make_shared<Skybox>(skybox_data);
    skybox->set_cubemap(cubemap);
    
    // ------------------
    
    // pyramid
    
    auto pyramid_data = ObjectData<float>{};
    
    pyramid_data
        .set_data(get_pyramide())
        .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0})
        .set_attribute_pointer(AttributePointer{1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))})
        .set_attribute_pointer(AttributePointer{2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))});
    
    pyramid_data.compute_and_add_normals_and_tangents();
    
    auto normals = pyramid_data.get_normals();
    
    auto pyramid = std::make_shared<Object>(pyramid_data);
    
    auto is_toy = true;
    
    if (is_toy)
    {
        pyramid->set_diffuse(toy_diffuse)
        .set_normal_map(toy_normal)
        .set_disp_map(toy_disp);
    }
    else
    {
        pyramid->set_diffuse(bricks2_diffuse)
        .set_normal_map(bricks2_normal)
        .set_disp_map(bricks2_disp)
        ;
    }
    
    //pyramid->get_draw_parameters().outlined = true;
    
    pyramid->rotate(glm::pi<float>(), glm::vec3(0.0f, 1.0f, 0.0f));
    
    auto snd_pyramid = std::make_shared<Object>(*pyramid);
    
    snd_pyramid->translate(glm::vec3(2.0f, 2.0f, -2.0f));
    
    // -------------------------------------
    
    glm::mat4 model {1.0f};
    
    // light
    
    auto dir_light = std::make_shared<DirectionalLight>(glm::vec3(0.0f, -1.0f, 0.0f));   // vertical light
    auto dir_light_actor = std::make_shared<DirLightActor>(dir_light);
    
    auto point_light = std::make_shared<PointLight>(glm::vec3(0.3f, 1.0f, 0.3f));
    auto point_light_actor = std::make_shared<PointLightActor>(point_light);
    
    auto light_data = ObjectData<float>::create_data()
    .set_data(get_light_cube())
    .set_attribute_pointer(AttributePointer{0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0})
    .set_attribute_pointer(AttributePointer{1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))});
    
    auto light = std::make_shared<Object>(light_data);
    
    light->translate(glm::vec3(2.0f, 2.0f, 2.0f));
    //.scale(glm::vec3(0.2f, 0.2f, 0.2f));
    
    // ----------------------------     scene
    
    scene.set_skybox(skybox, skybox_shader);
    scene.add_object(earth_obj);
    scene.add_light(dir_light);
    scene.add_light(point_light);
    scene.pre_cycle_init();

    std::cout << "OpenGL version: " << glGetString(GL_VERSION);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // main loop stuff
    
    auto last_frame = 0.0f;
    auto current_frame = 0.0f;
    
    // Loop until the user closes the window
    while(!glfwWindowShouldClose(window))
    {
        current_frame = glfwGetTime();
        
        auto delta = current_frame - last_frame;
        last_frame = current_frame;
        
        CommandProcessor::ApplyCommand(input_controller.try_get_movement_cmd(window, delta), camera);
        CommandProcessor::ApplyCommand(input_controller.try_get_view_cmd(window, delta), camera);
        CommandProcessor::ApplyCommand(input_controller.try_process_secondary_movement(window, delta, 2.0f), point_light_actor);
        CommandProcessor::ApplyCommand(input_controller.try_process_secondary_rotation(window, delta), dir_light_actor);
        
        // Render here!
        glStencilMask(0xFF);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);                // move buffer clearing to the renderer
        glStencilMask(0x00);
        
        renderer->draw_scene(scene);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
}

void clean_up()
{
    glfwTerminate();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina displays
    glViewport(0, 0, width, height);
}
