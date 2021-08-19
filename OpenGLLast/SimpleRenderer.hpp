//
//  SimpleRenderer.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.05.2021.
//

#ifndef SimpleRenderer_hpp
#define SimpleRenderer_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include "Shader.hpp"
#include "ShaderProgram.hpp"

#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "Texture.hpp"
#include "ITexture.hpp"

#include "Vector.hpp"
#include "Object.hpp"
#include "ObjectData.hpp"

#include "Camera.hpp"
#include "Move.hpp"
#include "Rotate.hpp"

#include "Presets.hpp"

#include "Scene.hpp"

#include <assimp/Importer.hpp>

#include "CommandProccessor.hpp"

#include "Path.hpp"

void deffered_renderer(GLFWwindow* window);

#endif /* SimpleRenderer_hpp */
