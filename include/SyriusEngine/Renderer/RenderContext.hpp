#pragma once

#include "Primitives.hpp"
#include "ShaderLibrary.hpp"
#include "../Utils/Worker.hpp"

namespace Syrius{

    class SR_API RenderContext{
    public:
        RenderContext(ResourceView<Context>& context, Worker& renderThread, ResourceView<Sampler>& defaultSampler, const std::string& shaderLibraryPath);

        RenderContext() = delete;

        ~RenderContext();

    private:
        friend class RenderLayer;
        friend class Renderer;

    private:
        ResourceView<Context>& m_Context;
        ResourceView<Sampler>& m_DefaultSampler;
        Worker& m_RenderThread;
        UP<ShaderLibrary> m_ShaderLibrary;




    };

}