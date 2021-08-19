//
//  ObjectData.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 14.04.2021.
//

#ifndef ObjectData_hpp
#define ObjectData_hpp

#include "AttributePointers.hpp"

#include <glm/glm.hpp>

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
    
    bool compute_and_add_normals_and_tangents()
    {
        const std::size_t tex_coords_offset = 6;    // texCoords come after pos and color info, thus 6 offset
        
        if (!validate())
        {
            return false;
        }
        
        size_t stride = attr_pointers[0].stride / sizeof(float);
        
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> tangents;
        std::vector<glm::vec3> bTangents;
        
        auto v_count = get_vertex_count();
        
        normal_vectors.clear();
        normal_vectors.reserve(v_count);
        
        normals.reserve(v_count);
        
        std::vector<glm::vec3> pos_triangle {3};
        std::vector<glm::vec2> tex_coords_triangle {3};
        
        for (auto i = 0; i < v_count; i++)
        {
            auto x = data[i * stride];
            auto y = data[i * stride + 1];
            auto z = data[i * stride + 2];
            
            auto u = data[i * stride + tex_coords_offset];
            auto v = data[i * stride + tex_coords_offset + 1];
            
            pos_triangle[i % 3] = glm::vec3(x, y, z);
            tex_coords_triangle[i % 3] = glm::vec2(u, v);
            
            if ((i + 1) % 3 == 0)
            {
                auto vec1 = glm::normalize(pos_triangle[1] - pos_triangle[0]);
                auto vec2 = glm::normalize(pos_triangle[2] - pos_triangle[0]);
                
                normals.emplace_back(glm::normalize(glm::cross(vec1, vec2)));
                
                // computing tangents
                
                auto delta1 = glm::normalize(tex_coords_triangle[1] - tex_coords_triangle[0]);
                auto delta2 = glm::normalize(tex_coords_triangle[2] - tex_coords_triangle[0]);
                
                auto det = delta1.x * delta2.y - delta2.x * delta1.y;
                
                glm::vec3 tangent {};
                glm::vec3 bTangent {};
                
                tangent.x = (delta2.y * vec1.x - delta1.y * vec2.x) / det;                   // TODO: replace with matrix calculation
                tangent.y = (delta2.y * vec1.y - delta1.y * vec2.y) / det;
                tangent.z = (delta2.y * vec1.z - delta1.y * vec2.z) / det;
                
                bTangent.x = (-delta2.x * vec1.x + delta1.x * vec2.x) / det;
                bTangent.y = (-delta2.x * vec1.y + delta1.x * vec2.y) / det;
                bTangent.z = (-delta2.x * vec1.z + delta1.x * vec2.z) / det;
                
                tangents.emplace_back(tangent);
                bTangents.emplace_back(bTangent);                                  // what z coordinates should be equal to???
                
                //
                
                normal_vectors.emplace_back(std::make_pair(pos_triangle[0], normals[normals.size() - 1]));
                normal_vectors.emplace_back(std::make_pair(pos_triangle[1], normals[normals.size() - 1]));
                normal_vectors.emplace_back(std::make_pair(pos_triangle[2], normals[normals.size() - 1]));
            }
        }
        
        std::vector<float> new_data;
        new_data.reserve(data.size() + (normals.size() + tangents.size() + bTangents.size()) * 3 * 3);          // for each vertex there is a normal, so 9 additional float components for each triangle
        
        
        for (auto i = 0; i < data.size(); i++)
        {
            new_data.emplace_back(data[i]);
            
            if ((i + 1) % stride == 0)
            {
                auto current_triagle_i = i / (stride * 3);
                
                new_data.emplace_back(normals[current_triagle_i].x);
                new_data.emplace_back(normals[current_triagle_i].y);
                new_data.emplace_back(normals[current_triagle_i].z);
                
                new_data.emplace_back(tangents[current_triagle_i].x);
                new_data.emplace_back(tangents[current_triagle_i].y);
                new_data.emplace_back(tangents[current_triagle_i].z);
                
                new_data.emplace_back(bTangents[current_triagle_i].x);
                new_data.emplace_back(bTangents[current_triagle_i].y);
                new_data.emplace_back(bTangents[current_triagle_i].z);
            }
        }
        
        data = new_data;
        
        auto new_stride = (int) (stride + 9) * sizeof(float);
        
        for (auto& attr : attr_pointers)
        {
            attr.stride = new_stride;
        }
        
        AttributePointer normals_attr {(int)attr_pointers.size(), 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(new_stride), (void*) (sizeof(float) * stride) };
        AttributePointer tangents_attr {(int)attr_pointers.size() + 1, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(new_stride), (void*) (sizeof(float) * (stride + 3))};
        AttributePointer bTangents_attr {(int)attr_pointers.size() + 2, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(new_stride), (void*) (sizeof(float) * (stride + 6))};
        
        attr_pointers.push_back(normals_attr);
        attr_pointers.push_back(tangents_attr);
        attr_pointers.push_back(bTangents_attr);
        
        return true;
    }
    
    static ObjectData create_data()
    {
        return ObjectData();
    }
    
    std::vector<std::pair<glm::vec3, glm::vec3>> get_normals () {return normal_vectors;}         // DEBUG PROP
    
private:
    std::vector<T> data;
    std::vector<AttributePointer> attr_pointers;
    
    // runtime
    GLsizei vertex_count = 0;
    
    std::vector<std::pair<glm::vec3, glm::vec3>> normal_vectors;               // DEBUG
};

#endif /* ObjectData_hpp */
