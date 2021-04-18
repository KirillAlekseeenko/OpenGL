//
//  VertexBufferObject.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#ifndef VertexBufferObject_hpp
#define VertexBufferObject_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class VertexBufferObject
{
public:
    VertexBufferObject(GLenum target);
    
    ~VertexBufferObject();
    
    void initialize(const std::vector<float> &data, bool is_static);            // TODO: think of a way to make a template with some 'data type'
    void set_attrib_pointer(GLint index, GLint size_per_vertex, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset);
    
    VertexBufferObject(const VertexBufferObject& v) = delete;
    VertexBufferObject& operator=(const VertexBufferObject& v) = delete;
    
    VertexBufferObject(VertexBufferObject&& v);
    VertexBufferObject& operator=(VertexBufferObject&& v);
    
    GLuint get_handler() const { return handler; }                                 // TODO: create abstract opengl object
private:
    GLuint handler = 0;
    GLenum target;
};

#endif /* VertexBufferObject_hpp */
