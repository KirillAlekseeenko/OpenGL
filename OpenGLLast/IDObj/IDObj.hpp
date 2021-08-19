//
//  IDObj.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 24.04.2021.
//

#ifndef IDObj_hpp
#define IDObj_hpp

class IDObj
{
public:
    int get_id() const;
protected:
    IDObj();
private:
    int id;
    
    static int current_id;
};

#endif /* IDObj_hpp */
