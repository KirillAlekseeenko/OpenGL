//
//  VertexBufferObject.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#include "VertexBufferObject.hpp"

VertexBufferObject::VertexBufferObject(GLenum t) : target{t}
{
    glGenBuffers(1, &handler);
}

VertexBufferObject::VertexBufferObject(VertexBufferObject&& v)
{
    handler = v.handler;
    target = v.target;
    v.handler = 0;
}
VertexBufferObject& VertexBufferObject::operator=(VertexBufferObject&& v)
{
    glBindBuffer(target, 0);
    
    if (handler != v.handler)
    {
        glDeleteBuffers(1, &handler);
        handler = v.handler;
        target = v.target;
    }
    
    v.handler = 0;
    
    return *this;
}

void VertexBufferObject::initialize(const std::vector<float> &data, bool is_static)
{
    glBindBuffer(target, handler);
    
    glBufferData(
                 target,
                 sizeof(float) * data.size(),
                 data.data(),
                 is_static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    
    glBindBuffer(target, 0);
}

void VertexBufferObject::set_attrib_pointer(
                                            GLint index,
                                            GLint size_per_vertex,
                                            GLenum type,
                                            GLboolean normalized,
                                            GLsizei stride,
                                            const GLvoid* offset)
{
    glBindBuffer(target, handler);
    
    glVertexAttribPointer(index, size_per_vertex, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
    
    glBindBuffer(target, 0);
}

VertexBufferObject::~VertexBufferObject()
{
    if (handler != 0)
    {
        glDeleteBuffers(1, &handler);
    }
}
