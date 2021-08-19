//
//  Cubemap.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 26.05.2021.
//

#ifndef Cubemap_hpp
#define Cubemap_hpp

#include "ITexture.hpp"
#include "TextureInfo.hpp"

#include <array>
#include <vector>

#include "Path.hpp"

class Cubemap : public ITexture
{
    static constexpr std::size_t CUBEMAP_SIDES_COUNT = 6;
public:
    ~Cubemap();
    
    Cubemap();
    
    // TODO: incapsulate texture data from stbi_load in some class
    Cubemap(std::array<std::string, CUBEMAP_SIDES_COUNT> map_paths);
    
    Cubemap(const Cubemap& t) = delete;
    Cubemap& operator=(const Cubemap& t) = delete;
    
    Cubemap(Cubemap&& t);
    Cubemap& operator=(Cubemap&& t);
    
    void load_to_vram(GLenum type = GL_UNSIGNED_BYTE) override;
    
    void set_wrap_s(GLint type) override;
    void set_wrap_t(GLint type) override;
    void set_wrap_r(GLint type) override;
    
    void set_min_filter(GLint type) override;
    void set_mag_filter(GLint type) override;
    
    GLuint get_handle() const override { return handle; }                                 // TODO: create abstract opengl object
    
    std::string get_name() const override;
    
    bool is_valid() const override
    {
        return std::all_of(textures_info.begin(), textures_info.end(), [](const TextureInfo &info) {return info.is_valid();});
    }
    
    static std::unique_ptr<ITexture> create_cubemap(Dir dir, std::array<std::string, CUBEMAP_SIDES_COUNT> map_paths, GLenum type = GL_UNSIGNED_BYTE);
    
private:
    GLuint handle = 0;
    GLenum target = 0;
    
    std::vector<TextureInfo> textures_info = std::vector<TextureInfo>(CUBEMAP_SIDES_COUNT);
    
    std::string name;
private:
    
    void binded(std::function<void(void)> action)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
        
        action();
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
    
};

#endif /* Cubemap_hpp */
