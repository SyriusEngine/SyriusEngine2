#include "Renderer.hpp"

namespace Syrius{

    // TEST IMAGE
    static ResourceView<Texture2D> testTexture;

    Renderer::Renderer(const RendererDesc &rendererDesc, UP<LayerStack>& layerStack, Resource<SyriusWindow>& window):
    m_LayerStack(layerStack),
    m_Window(window),
    m_Worker(){
        m_Worker.start();
        m_Worker.pushTaskSync([rendererDesc, this]{ // do NOT take rendererDesc in via reference!!

            ContextDesc contextDesc;
            contextDesc.api = rendererDesc.api;
            m_Context = m_Window->createContext(contextDesc);

            SamplerDesc splrDesc;
            splrDesc.minFilter = SR_TEXTURE_FILTER_LINEAR;
            splrDesc.magFilter = SR_TEXTURE_FILTER_LINEAR;
            splrDesc.wrapU = SR_TEXTURE_WRAP_REPEAT;
            splrDesc.wrapV = SR_TEXTURE_WRAP_REPEAT;
            auto defaultSampler = m_Context->createSampler(splrDesc);

            m_RenderContext = createUP<RenderContext>(m_Context, m_Worker, defaultSampler, rendererDesc.shaderLibraryPath);
            setup();

            auto img = createImage("./Resources/Textures/awesomeface.png");
            Texture2DImageDesc t2diDesc;
            t2diDesc.image = img.createView();
            t2diDesc.sampler = defaultSampler;
            testTexture = m_Context->createTexture2D(t2diDesc);

        });
    }

    Renderer::~Renderer() {
        m_Worker.pushTaskSync([this]{
            m_Window->destroyContext();
        });
        m_Worker.stop();
    }

    void Renderer::render() {
        m_Worker.pushTaskSync([this]{

            auto defaultfbo = m_Context->getDefaultFrameBuffer();
            defaultfbo = m_LayerStack->onRender(defaultfbo);

            m_Context->beginRenderPass();
            testTexture->bind(0); //TODO: replace with defaultfbo object
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

}
