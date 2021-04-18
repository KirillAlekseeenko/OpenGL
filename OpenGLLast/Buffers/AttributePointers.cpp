//
//  AttributePointers.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.04.2021.
//

#include "AttributePointers.hpp"

AttributePointer::AttributePointer(GLint i,
                 GLint sz_p_v,
                 GLenum t,
                 GLboolean n,
                 GLsizei st,
                 GLvoid* o)
: index{i},
  size_per_vertex{sz_p_v},
  type{t},
  normalized{n},
  stride{st},
  offset{o}
{
}
