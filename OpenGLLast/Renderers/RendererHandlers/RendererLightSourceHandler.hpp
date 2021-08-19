//
//  RendererLightSourceHandler.hpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 03.07.2021.
//

#ifndef RendererLightSourceHandler_hpp
#define RendererLightSourceHandler_hpp

#include "ILightSource.hpp"
#include "ITexture.hpp"
#include "Framebuffer.hpp"


class RendererLightSourceHandle
{
public:
    
    using ShadowMapsCacheType = std::vector<std::shared_ptr<ITexture>>;
    
    RendererLightSourceHandle(std::shared_ptr<ILightSource> l, int shadow_maps_count = 1);
    
    std::shared_ptr<ILightSource> get_light() const;
    const std::shared_ptr<Framebuffer>& get_framebuffer() const;
    ShadowMapsCacheType& get_maps();
    
    void load_to_vram();
    
private:
    std::shared_ptr<ILightSource> light;
    std::shared_ptr<Framebuffer> depth_framebuffer;
    std::vector<std::shared_ptr<ITexture>> shadow_maps_cache;
    
};

#endif /* RendererLightSourceHandler_hpp */
