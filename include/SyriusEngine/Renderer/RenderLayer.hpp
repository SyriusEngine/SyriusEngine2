#pragma once

#include "Primitives.hpp"
#include "RenderContext.hpp"
#include "../Layer.hpp"

namespace Syrius{

    class SR_API RenderLayer: public Layer{
    public:
        ~RenderLayer() override;

        virtual ResourceView<FrameBuffer>& onRender(ResourceView<FrameBuffer>& framebuffer) = 0;

    protected:
        explicit RenderLayer(const UP<RenderContext>& renderContext);

    protected:
        ResourceView<Context>& m_Context;
        ResourceView<Sampler>& m_DefaultSampler;
        Worker& m_RenderThread;


    };

}
