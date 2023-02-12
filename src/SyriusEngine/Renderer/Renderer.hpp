#pragma once

#include "../../../include/SyriusEngine/Renderer/Primitives.hpp"
#include "../../../include/SyriusEngine/Utils/Worker.hpp"
#include "../LayerStack.hpp"

namespace Syrius{

    struct RendererDesc{
        SR_SUPPORTED_API api;
        std::string shaderLibraryPath;
    };

    class Renderer{
    public:
        explicit Renderer(const RendererDesc& rendererDesc, UP<LayerStack>& layerStack, Resource<SyriusWindow>& window);

        ~Renderer();

        void render();

        [[nodiscard]] const UP<RenderContext>& getRenderContext() const;


    private:

        void setup();

    private:

        UP<LayerStack>& m_LayerStack;
        Resource<SyriusWindow>& m_Window;
        Worker m_Worker;

        ResourceView<Context> m_Context;

        UP<RenderContext> m_RenderContext;

        ResourceView<VertexArray> m_ScreenVAO;
        ResourceView<VertexBuffer> m_ScreenVBO;
        ResourceView<IndexBuffer> m_ScreenIBO;
        ResourceView<Shader> m_ScreenShader;

    };

}