#include "GeometryPass.hpp"

namespace Syrius{

    ResourceView<FrameBufferDescription> createGeometryPassFramebufferDesc(ResourceView<Context>& context){
        ViewportDesc vpDesc;
        vpDesc.width = context->getWidth();
        vpDesc.height = context->getHeight();

        ColorAttachmentDesc colorAttachmentDesc;
        colorAttachmentDesc.width = vpDesc.width;
        colorAttachmentDesc.height = vpDesc.height;
        colorAttachmentDesc.format = SR_TEXTURE_DATA_FORMAT_RGBA_F32;

        DepthStencilAttachmentDesc dsaDesc;
        dsaDesc.width = vpDesc.width;
        dsaDesc.height = vpDesc.height;
        dsaDesc.enableDepthTest = true;

        auto fbDesc = context->createFrameBufferDescription();
        fbDesc->addViewportDesc(vpDesc);
        fbDesc->addDepthStencilAttachmentDesc(dsaDesc);
        fbDesc->addColorAttachmentDesc(colorAttachmentDesc);
        return fbDesc;
    }


    GeometryPass::GeometryPass(ResourceView<Context> &context, UP<ShaderLibrary> &shaderLibrary):
    RenderPass(context, createGeometryPassFramebufferDesc(context)){
        m_VertexDescription->addAttribute("Position", SR_FLOAT32_3);
        m_VertexDescription->addAttribute("Normal", SR_FLOAT32_3);
        m_VertexDescription->addAttribute("Tangent", SR_FLOAT32_3);
        m_VertexDescription->addAttribute("TexCoords", SR_FLOAT32_2);

        auto package = shaderLibrary->getPackage("GeometryPass");
        m_VertexShaderModule = package.vertexShader;
        m_Shader = m_Context->createShader(package);

        ConstantBufferDesc cbDesc;
        cbDesc.name = "ModelData";
        cbDesc.size = sizeof(MeshTransformation);
        cbDesc.slot = 2;
        cbDesc.type = SR_BUFFER_DYNAMIC;
        cbDesc.shaderStage = SR_SHADER_VERTEX;
        MeshTransformation defaultData;
        cbDesc.data = &defaultData;
        m_ModelData = m_Context->createConstantBuffer(cbDesc);
    }

    GeometryPass::~GeometryPass() {

    }

    void GeometryPass::execute() {
        executeInputPasses();

        m_Context->beginRenderPass(m_FrameBuffer);

        m_ModelData->bind();
        m_Shader->bind();
        for (const auto& data: m_Meshes){
            m_ModelData->setData(&data.transformation);
            m_Context->draw(data.vertexArray);
        }
        m_Context->endRenderPass(m_FrameBuffer);
    }

    MeshID GeometryPass::createMesh(const MeshDesc &meshDesc) {
        MeshHandle handle;

        VertexBufferDesc vbDesc;
        vbDesc.data = meshDesc.vertices.data();
        vbDesc.count = meshDesc.vertices.size();
        vbDesc.layout = m_VertexDescription;
        vbDesc.type = SR_BUFFER_STATIC;
        handle.vertexBuffer = m_Context->createVertexBuffer(vbDesc);

        IndexBufferDesc ibDesc;
        ibDesc.data = meshDesc.indices.data();
        ibDesc.count = meshDesc.indices.size();
        ibDesc.type = SR_BUFFER_STATIC;
        ibDesc.dataType = SR_UINT32;
        handle.indexBuffer = m_Context->createIndexBuffer(ibDesc);

        VertexArrayDesc vaDesc;
        vaDesc.vertexBuffer = handle.vertexBuffer;
        vaDesc.indexBuffer = handle.indexBuffer;
        vaDesc.vertexShader = m_VertexShaderModule;
        handle.vertexArray = m_Context->createVertexArray(vaDesc);

        handle.materialID = meshDesc.materialID;
        MeshID mid = generateID();
        m_Meshes.insert(mid, handle);
        return mid;
    }

    void GeometryPass::setMeshTransformation(MeshID mid, const glm::mat4 &modelMatrix) {
        auto& handle = m_Meshes[mid];
        handle.transformation.modelMatrix = modelMatrix;
        handle.transformation.normalMatrix = glm::transpose(glm::inverse(modelMatrix));
    }

    void GeometryPass::removeMesh(MeshID mid) {
        m_Meshes.remove(mid);
    }
}