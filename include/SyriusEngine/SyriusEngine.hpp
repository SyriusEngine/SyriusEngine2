#pragma once

#include "Layer.hpp"
#include "Debug.hpp"

#include "Renderer/Primitives.hpp"
#include "Renderer/RenderLayer.hpp"

#include "ECS/ECS.hpp"

namespace Syrius{

    struct SR_API SyriusEngineDesc{
        WindowDesc window;
        SR_SUPPORTED_API renderAPI = SR_API_OPENGL;
        std::string shaderLibraryPath;
    };

    class SR_API SyriusEngine{
    public:
        virtual ~SyriusEngine();

        virtual void run() = 0;

        virtual void pushLayer(RCP<Layer> layer) = 0;

        virtual void pushRenderLayer(RCP<RenderLayer> renderLayer) = 0;

        virtual void popLayer(uint32 popCount) = 0;

        virtual void close() = 0;

        [[nodiscard]] virtual const UP<RenderContext>& getRenderContext() const = 0;

        ResourceView<SyriusWindow> getInternalWindow();

    protected:

        explicit SyriusEngine(const SyriusEngineDesc& desc);

    protected:
        Resource<SyriusWindow> m_Window;
        UP<ECS> m_ECS;

    };

    SR_API void init();

    SR_API void terminate();

    SR_API UP<SyriusEngine> createEngine(const SyriusEngineDesc& desc);

}