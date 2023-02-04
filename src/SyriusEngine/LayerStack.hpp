#pragma once

#include "../../include/SyriusEngine/Include.hpp"
#include "../../include/SyriusEngine/Layer.hpp"
#include "../../include/SyriusEngine/Renderer/RenderLayer.hpp"

namespace Syrius{

    class LayerStack{
    public:
        LayerStack();

        ~LayerStack();

        void pushLayer(RCP<Layer> layer);

        void pushRenderLayer(RCP<RenderLayer> renderLayer);

        void popLayer(uint32 popCount = 1);

        void onUpdate();

        void onEvent(const Event& event);

    protected:

        friend class RenderCommand;

        ResourceView<FrameBuffer>& onRender(ResourceView<FrameBuffer>& framebuffer);

    private:
        std::vector<RCP<Layer>> m_Layers;
        std::vector<RCP<RenderLayer>> m_RenderLayers;
    };


}