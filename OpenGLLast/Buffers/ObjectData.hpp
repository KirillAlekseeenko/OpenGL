//
//  ObjectData.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.04.2021.
//

#ifndef ObjectData_hpp
#define ObjectData_hpp

#include "AttributePointers.hpp"

#include <vector>

template<class T>
class ObjectData
{
public:
    ObjectData(){}
    ObjectData(std::vector<T> d) : data{std::move(d)}
    {
    }
    
    ObjectData(const ObjectData &o) : data{o.data}, attr_pointers{o.attr_pointers}
    {
    }
    ObjectData& operator=(const ObjectData &o)
    {
        data = o.data;
        attr_pointers = o.attr_pointers;
        return *this;
    }
    
    ObjectData(ObjectData &&o) : data{std::move(o.data)}, attr_pointers{std::move(o.attr_pointers)}
    {
    }
    ObjectData& operator=(ObjectData &&o)
    {
        data = std::move(o.data);
        attr_pointers = std::move(o.attr_pointers);
        return *this;
    }
    
    ObjectData& set_data(std::vector<T> d)
    {
        data = std::move(d);
        return *this;
    }
    std::vector<T>& get_data_ref()
    {
        return data;
    }
    
    ObjectData& set_attribute_pointer(AttributePointer a)
    {
        attr_pointers.push_back(std::move(a));
        return *this;
    }
    std::vector<AttributePointer>& get_attributes_ref()
    {
        return attr_pointers;
    }
    
    GLsizei get_vertex_count()
    {
        if (vertex_count != 0) return vertex_count;                                             // TODO: not reliable
        
        if (attr_pointers.size() == 0) return 0;
        
        vertex_count = (int)(sizeof(T) * data.size()) / attr_pointers[0].stride;
        
        return vertex_count;
    }
    
    bool validate()
    {
        if (attr_pointers.size() == 0) return false;
        
        GLsizei stride = attr_pointers[0].stride;
        for (const auto& attr : attr_pointers)
        {
            if (stride != attr.stride) return false;               // stride should be the same
        }
        
        vertex_count = (int)(sizeof(T) * data.size()) / attr_pointers[0].stride;
        
        return true;
    }
    
    static ObjectData create_data()
    {
        return ObjectData();
    }
    
private:
    std::vector<T> data;
    std::vector<AttributePointer> attr_pointers;
    
    // runtime
    GLsizei vertex_count = 0;
};

#endif /* ObjectData_hpp */
