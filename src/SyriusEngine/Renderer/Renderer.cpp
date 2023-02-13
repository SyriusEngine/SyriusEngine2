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

            SamplerDesc splrDesc;
            splrDesc.minFilter = SR_TEXTURE_FILTER_LINEAR;
            splrDesc.magFilter = SR_TEXTURE_FILTER_LINEAR;
            splrDesc.wrapU = SR_TEXTURE_WRAP_REPEAT;
            splrDesc.wrapV = SR_TEXTURE_WRAP_REPEAT;
            m_Sampler = m_Context->createSampler(splrDesc);

            m_RenderContext = createUP<RenderContext>(m_Context, m_Worker, m_Sampler, rendererDesc.shaderLibraryPath);
            setup();
        });

        m_PBRenderLayer = createRCP<PBRenderLayer>(m_RenderContext);
        m_LayerStack->pushRenderLayer(m_PBRenderLayer);

        MeshDesc cube;
        cube.vertices = {
                /// front
                {glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// left
                {glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// bottom
                {glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// back
                {glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(0.0f, 1.0f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// right
                {glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
                /// top
                {glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(1.0f, 0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        };
        cube.indices = {
                0, 3, 2,
                0, 2, 1,

                4, 7, 6,
                4, 6, 5,

                8, 11, 10,
                8, 10, 9,

                12, 15, 14,
                12, 14, 13,

                16, 19, 18,
                16, 18, 17,

                20, 23, 22,
                20, 22, 21
        };

        auto mid = m_PBRenderLayer->createMesh(cube);
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
