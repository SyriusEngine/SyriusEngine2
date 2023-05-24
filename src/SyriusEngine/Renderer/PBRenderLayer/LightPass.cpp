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
    m_LightCount(0),
    m_GeometryPass(geometryPass){
        addDependency(GEOMETRY_PASS);

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

        ConstantBufferDesc cbDesc;
        cbDesc.name = "LightData";
        cbDesc.size = sizeof(LightData);
        cbDesc.slot = 3;
        LightData cData;
        cbDesc.data = &cData;
        cbDesc.type = SR_BUFFER_DYNAMIC;
        cbDesc.shaderStage = SR_SHADER_FRAGMENT;
        m_LightDataBuffer = m_Context->createConstantBuffer(cbDesc);

    }

    LightPass::~LightPass() {

    }

    void LightPass::execute() {
        m_Context->beginRenderPass(m_FrameBuffer);

        m_Shader->bind();
        m_LightDataBuffer->bind();

        for (uint32 i = 0; i < 4; i++){
            m_GeometryPass->getFrameBuffer()->getColorAttachment(i)->bindShaderResource(i);
        }
        m_Context->draw(m_ScreenVAO);
        m_Context->endRenderPass(m_FrameBuffer);
}

    LightID LightPass::createLight(const LightDesc& desc) {
        LightID lid = generateID();

        m_LightData.m_Position[m_LightCount] = glm::vec4(desc.position, 1.0f);
        m_LightData.m_Color[m_LightCount] = glm::vec4(desc.color, 1.0f);
        m_LightData.m_LightCount[0]++;
        m_KeyLightMap.insert({lid, m_LightCount});
        m_LightCount++;

        m_LightDataBuffer->setData(&m_LightData);

        return lid;
    }

    void LightPass::removeLight(LightID index) {
        auto lastIndex = m_LightCount - 1;
        for (const auto& pair: m_KeyLightMap){
            if (lastIndex == pair.second){
                //switch current light with last light
                m_LightData.m_Position[m_KeyLightMap[index]] = m_LightData.m_Position[lastIndex];
                m_LightData.m_Color[m_KeyLightMap[index]] = m_LightData.m_Color[lastIndex];
                //clear last light
                m_LightData.m_Position[lastIndex] = glm::vec4(0.0f);
                m_LightData.m_Color[lastIndex] = glm::vec4(0.0f);
            }
        }
    }
}
