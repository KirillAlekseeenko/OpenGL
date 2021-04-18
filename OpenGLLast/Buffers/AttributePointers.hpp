//
//  AttributePointers.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.04.2021.
//

#ifndef AttributePointers_hpp
#define AttributePointers_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class AttributePointer
{
public:
    AttributePointer(GLint index,
                     GLint size_per_vertex,
                     GLenum type,
                     GLboolean normalized,
                     GLsizei stride,
                     GLvoid* offset);
    
    GLint index;
    GLint size_per_vertex;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    GLvoid* offset;
};

#endif /* AttributePointers_hpp */
