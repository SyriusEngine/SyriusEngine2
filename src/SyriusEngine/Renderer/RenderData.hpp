#pragma once

#include "../../../include/SyriusEngine/Renderer/Primitives.hpp"
#include "../../../include/SyriusEngine/Renderer/ShaderLibrary.hpp"

namespace Syrius{

    struct RenderData{
        ResourceView<Context>& context;
        ResourceView<Sampler>& defaultSampler;
        UP<ShaderLibrary>& shaderLibrary;

        RenderData() = delete;

        RenderData(ResourceView<Context>& context, ResourceView<Sampler>& defaultSampler, UP<ShaderLibrary>& shaderLibrary);

        ~RenderData() = default;
    };

}