#pragma once

#include "../../include/SyriusEngine/SyriusEngine.hpp"
#include "LayerStack.hpp"
#include "Renderer/Renderer.hpp"

namespace Syrius{

    class SyriusEngineImpl: public SyriusEngine{
    public:
        explicit SyriusEngineImpl(const SyriusEngineDesc& desc);

        ~SyriusEngineImpl() override;

        void run() override;

        void pushLayer(RCP<Layer> layer) override;

        void pushRenderLayer(RCP<RenderLayer> renderLayer) override;

        void popLayer(uint32 popCount) override;

        void close() override;

        [[nodiscard]] const UP<RenderContext>& getRenderContext() const override;

    private:
        UP<LayerStack> m_LayerStack;
        UP<Renderer> m_Renderer;

    };

}