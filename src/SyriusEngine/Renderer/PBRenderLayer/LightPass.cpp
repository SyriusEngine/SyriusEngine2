#include "LightPass.hpp"

namespace Syrius{

    ResourceView<FrameBufferDescription> createLightPassFramebufferDesc(ResourceView<Context>& context){
        ViewportDesc vpDesc;
        vpDesc.width = context->getWidth();
        vpDesc.height = context->getHeight();

        ColorAttachmentDesc f32Attachment;
        f32Attachment.width = vpDesc.width;
        f32Attachment.height = vpDesc.height;
        f32Attachment.format = SR_TEXTURE_RGBA_F32;

        auto fbDesc = context->createFrameBufferDescription();
        fbDesc->addViewportDesc(vpDesc);
        fbDesc->addColorAttachmentDesc(f32Attachment); // final color
        return fbDesc;
    }


    LightPass::LightPass(const RenderData& renderData, RCP<GeometryPass>& geometryPass) :
    RenderPass(renderData.context, createLightPassFramebufferDesc(renderData.context), LIGHTING_PASS),
    m_Sampler(renderData.defaultSampler),
    m_GeometryPass(geometryPass){
        addDependency(GEOMETRY_PASS);
        addDependency(LIGHT_DATA_PASS);
        addDependency(LINEAR_FILTER_WRAP_REPEAT_SAMPLER_PASS);

        m_VertexDescription->addAttribute("Position", SR_FLOAT32_2);
        m_VertexDescription->addAttribute("TexCoords", SR_FLOAT32_2);

        auto package = renderData.shaderLibrary->getPackage("LightPass");
        m_Shader = m_Context->createShader(package);

        VertexBufferDesc vbDesc;
        vbDesc.data = s_ScreenVertices;
        vbDesc.count = 4;
        vbDesc.layout = m_VertexDescription;
        vbDesc.type = SR_BUFFER_STATIC;

        m_ScreenVBO = m_Context->createVertexBuffer(vbDesc);

        IndexBufferDesc ibDesc;
        ibDesc.data = s_ScreenIndices;
        ibDesc.count = 6;
        ibDesc.type = SR_BUFFER_STATIC;
        ibDesc.dataType = SR_UINT32;

        m_ScreenIBO = m_Context->createIndexBuffer(ibDesc);

        VertexArrayDesc vaDesc;
        vaDesc.vertexBuffer = m_ScreenVBO;
        vaDesc.indexBuffer = m_ScreenIBO;
        vaDesc.vertexShader = package.vertexShader;
        m_ScreenVAO = m_Context->createVertexArray(vaDesc);

    }

    LightPass::~LightPass() {

    }

    void LightPass::execute() {
        m_Context->beginRenderPass(m_FrameBuffer);

        m_Shader->bind();
        for (uint32 i = 0; i < 4; i++){
            m_GeometryPass->getFrameBuffer()->getColorAttachment(i)->bindShaderResource(i);
        }
        m_Context->draw(m_ScreenVAO);
        m_Context->endRenderPass(m_FrameBuffer);
    }
}
