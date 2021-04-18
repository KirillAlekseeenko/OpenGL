//
//  VertexArrayObject.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 11.04.2021.
//

#ifndef VertexArrayObject_hpp
#define VertexArrayObject_hpp

#include "VertexBufferObject.hpp"

class VertexArrayObject
{
public:
    VertexArrayObject();
    ~VertexArrayObject();
    
    VertexArrayObject(const VertexArrayObject& v) = delete;
    VertexArrayObject& operator=(const VertexArrayObject& v) = delete;
    
    VertexArrayObject(VertexArrayObject&& v);
    VertexArrayObject& operator=(VertexArrayObject&& v);
    
    void use_binded(std::function<void(void)> op);
    
    GLuint get_handler() const { return handler; }
private:
    GLuint handler = 0;
};

#endif /* VertexArrayObject_hpp */
