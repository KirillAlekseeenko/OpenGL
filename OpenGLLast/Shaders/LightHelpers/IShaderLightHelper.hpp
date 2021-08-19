//
//  IShaderLightHelper.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 06.06.2021.
//

#ifndef IShaderLightHelper_hpp
#define IShaderLightHelper_hpp

#include "IShaderLightAdapter.hpp"

class IShaderLightHalper
{
public:
    virtual void apply(IShaderLightAdapter *s) = 0;
    
    virtual ~IShaderLightHalper() {}
};

#endif /* IShaderLightHelper_hpp */
