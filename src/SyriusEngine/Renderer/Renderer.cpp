#include "Renderer.hpp"

namespace Syrius{

    Renderer::Renderer(const RendererDesc &rendererDesc, UP<LayerStack>& layerStack, Resource<SyriusWindow>& window):
    m_LayerStack(layerStack),
    m_Window(window),
    m_Worker(){
        m_Worker.start();
        m_Worker.pushTaskSync([rendererDesc, this]{ // do NOT take rendererDesc in via reference!!

            ContextDesc contextDesc;
            contextDesc.api = rendererDesc.api;
            m_Context = m_Window->createContext(contextDesc);
            m_Context->setVerticalSynchronisation(true);

            SamplerDesc splrDesc;
            m_Sampler = m_Context->createSampler(splrDesc);

            m_RenderContext = createUP<RenderContext>(m_Context, m_Worker, m_Sampler, rendererDesc.shaderLibraryPath);
            setup();
        });

        m_PBRenderLayer = createRCP<PBRenderLayer>(m_RenderContext);
        m_LayerStack->pushRenderLayer(m_PBRenderLayer);
    }

    Renderer::~Renderer() {
        m_LayerStack.reset();
        m_Worker.pushTaskSync([this]{
            m_ScreenVAO.release();
            m_ScreenVBO.release();
            m_ScreenIBO.release();
            m_ScreenShader.release();
            m_Sampler.release();

            m_RenderContext.reset();

            m_Window->destroyContext();
            int x = 0; /// FOR SOME REASOM, IF I DELETE THIS LINE, THE ENGINE CRASHES WITH A SIGSEGV FAULT, THE HECK???
        });
        m_Worker.stop();
    }

    void Renderer::render() {
        m_Worker.pushTaskSync([this]{
            m_Sampler->bind(0);

            auto defaultfbo = m_Context->getDefaultFrameBuffer();
            defaultfbo = m_LayerStack->onRender(defaultfbo);

            m_Context->beginRenderPass();
            defaultfbo->getColorAttachment(0)->bindShaderResource(0);
            m_ScreenVAO->bind();
            m_ScreenShader->bind();
            m_Context->draw(m_ScreenVAO);
            m_Context->endRenderPass();

            m_Context->swapBuffers();
        });
    }

    const UP<RenderContext> &Renderer::getRenderContext() const {
        return m_RenderContext;
    }

    void Renderer::setup() {
        auto& package = m_RenderContext->m_ShaderLibrary->getPackage("Screen");
        m_ScreenShader = m_Context->createShader(package);

        auto vertexDesc = m_Context->createVertexDescription();
        vertexDesc->addAttribute("Position", SR_FLOAT32_2);
        vertexDesc->addAttribute("TexCoords", SR_FLOAT32_2);

        VertexBufferDesc vboDesc;
        vboDesc.data = s_ScreenVertices;
        vboDesc.type = SR_BUFFER_STATIC;
        vboDesc.count = 4;
        vboDesc.layout = vertexDesc;
        m_ScreenVBO = m_Context->createVertexBuffer(vboDesc);

        IndexBufferDesc iboDesc;
        iboDesc.data = s_ScreenIndices;
        iboDesc.count = 6;
        iboDesc.type = SR_BUFFER_STATIC;
        iboDesc.dataType = SR_UINT32;
        m_ScreenIBO = m_Context->createIndexBuffer(iboDesc);

        VertexArrayDesc vaoDesc;
        vaoDesc.indexBuffer = m_ScreenIBO;
        vaoDesc.vertexBuffer = m_ScreenVBO;
        vaoDesc.vertexShader = package.vertexShader;
        m_ScreenVAO = m_Context->createVertexArray(vaoDesc);
    }

    RCP<PBRenderLayer> &Renderer::getPBRenderLayer() {
        return m_PBRenderLayer;
    }

}
