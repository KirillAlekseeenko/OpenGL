//
//  VertexArrayObject.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#include "VertexArrayObject.hpp"


VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &handler);
}

VertexArrayObject::~VertexArrayObject()
{
    if (handler != 0)
    {
        glDeleteVertexArrays(1, &handler);
    }
}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& v)
{
    handler = v.handler;
    v.handler = 0;
}

VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject&& v)
{
    glBindVertexArray(0);
    
    if (handler != v.handler)
    {
        glDeleteVertexArrays(1, &handler);
        handler = v.handler;
    }
    
    v.handler = 0;
    
    return *this;
}

void VertexArrayObject::use_binded(std::function<void(void)> op)
{
    glBindVertexArray(handler);
    
    op();
    
    glBindVertexArray(0);
}
