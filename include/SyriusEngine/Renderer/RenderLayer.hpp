#pragma once

#include "Primitives.hpp"
#include "RenderContext.hpp"
#include "../Layer.hpp"

namespace Syrius{

    class SR_API RenderLayer: public Layer{
    public:
        ~RenderLayer() override;

        /**
         * @brief This function will be called once every frame. In this function, all draw calls should be placed to
         *        render something to a framebuffer. The framebuffer from the previous layer is supplied and can be used
         *        to be read from. You should return a framebuffer object containing at least one color attachment.
         *
         * @warning THIS FUNCTION IS DIRECTLY CALLED BY THE RENDER THREAD (same thread as the m_RenderThread member variable)
         * @param framebuffer Framebuffer from the previous render layer.
         * @return newly rendered frame
         */
        virtual ResourceView<FrameBuffer>& onRender(ResourceView<FrameBuffer>& framebuffer) = 0;

    protected:
        explicit RenderLayer(const UP<RenderContext>& renderContext);

    protected:
        ResourceView<Context>& m_Context;
        ResourceView<Sampler>& m_DefaultSampler;
        Worker& m_RenderThread;
        UP<ShaderLibrary>& m_ShaderLibrary;


    };

}
