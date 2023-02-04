#pragma once

#include "Primitives.hpp"
#include "../Layer.hpp"

namespace Syrius{

    class SR_API RenderLayer: public Layer{
    public:
        ~RenderLayer() override;

        virtual ResourceView<FrameBuffer>& onRender(ResourceView<FrameBuffer>& framebuffer) = 0;

    protected:
        explicit RenderLayer(ResourceView<Context>& context);

    protected:
        ResourceView<Context>& m_Context;


    };

}
