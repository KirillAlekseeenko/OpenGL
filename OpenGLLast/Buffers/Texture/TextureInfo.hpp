//
//  TextureInfo.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 29.05.2021.
//

#ifndef TextureInfo_h
#define TextureInfo_h

class TextureInfo
{
private:
    unsigned char* data = nullptr;
    
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    
public:
    
    int get_width() const {return width;};
    int get_height() const {return height;};
    int get_channels_count() const {return nrChannels;};
    
    const unsigned char* get_data() const {return data;}
    
    bool is_valid() const noexcept {return data != nullptr;}
    
    ~TextureInfo();
    TextureInfo() = default;
    
    TextureInfo(unsigned char* d, int w, int h, int nrChannels);
    
    TextureInfo& operator=(const TextureInfo& ti) = delete;
    TextureInfo(const TextureInfo& ti) = delete;
    
    TextureInfo& operator=(TextureInfo &&ti);
    TextureInfo(TextureInfo &&ti);
    
private:
    
    void set_to_default()
    {
        data = nullptr;
        width = 0;
        height = 0;
        nrChannels = 0;
    }
};
#endif /* TextureInfo_h */
