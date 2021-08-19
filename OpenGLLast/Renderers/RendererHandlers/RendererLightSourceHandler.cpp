//
//  RendererLightSourceHandler.cpp
//  OpenGLLast
//
//  Created by Кирилл Алексеенко on 03.07.2021.
//

#include "RendererLightSourceHandler.hpp"

#include "Texture.hpp"

RendererLightSourceHandle::RendererLightSourceHandle(std::shared_ptr<ILightSource> l, int shadow_maps_count)
: light{l},
  shadow_maps_cache(shadow_maps_count)
{
    depth_framebuffer = std::make_shared<Framebuffer>();
      
    switch(light->get_type())
    {
        case LightType::Directional:
        {
            for (auto i = 0; i < shadow_maps_cache.size(); i++)
            {
                auto depth_map = std::make_shared<Texture>();
                shadow_maps_cache[i] = depth_map;
            }
        }
            break;
        default: break;
    }
}

std::shared_ptr<ILightSource> RendererLightSourceHandle::get_light() const
{
    return light;
}

const std::shared_ptr<Framebuffer>& RendererLightSourceHandle::get_framebuffer() const
{
    return depth_framebuffer;
}


RendererLightSourceHandle::ShadowMapsCacheType& RendererLightSourceHandle::get_maps()
{
    return shadow_maps_cache;
}

void RendererLightSourceHandle::load_to_vram()
{
    for (auto& map : shadow_maps_cache)
    {
        map->load_to_vram();
    }
}
