#include "GeometryPass.hpp"


namespace Syrius{

    ResourceView<FrameBufferDescription> createGeometryPassFramebufferDesc(ResourceView<Context>& context){
        ViewportDesc vpDesc;
        vpDesc.width = context->getWidth();
        vpDesc.height = context->getHeight();

        ColorAttachmentDesc f32Attachment;
        f32Attachment.width = vpDesc.width;
        f32Attachment.height = vpDesc.height;
        f32Attachment.format = SR_TEXTURE_RGBA_F32;

        DepthStencilAttachmentDesc dsaDesc;
        dsaDesc.width = vpDesc.width;
        dsaDesc.height = vpDesc.height;
        dsaDesc.enableDepthTest = true;

        auto fbDesc = context->createFrameBufferDescription();
        fbDesc->addViewportDesc(vpDesc);
        fbDesc->addDepthStencilAttachmentDesc(dsaDesc);
        fbDesc->addColorAttachmentDesc(f32Attachment); //positions
        fbDesc->addColorAttachmentDesc(f32Attachment); //normals
        fbDesc->addColorAttachmentDesc(f32Attachment); //colors
        fbDesc->addColorAttachmentDesc(f32Attachment); // Smoothness, roughness and AO


        return fbDesc;
    }

    MaterialHandle::MaterialHandle(ResourceView<Context> &context, const MaterialDesc &matDesc) {
        auto createTexture = [&](ResourceView<Texture2D>& texture, ResourceView<Context>& context, const Resource<Image>& image) {
            Texture2DImageDesc desc(image);
            texture = context->createTexture2D(desc);
        };
        createTexture(m_Albedo, context, matDesc.albedo);
        createTexture(m_Normal, context, matDesc.normal);
        createTexture(m_Metallic, context, matDesc.metallic);
        createTexture(m_Roughness, context, matDesc.roughness);
        createTexture(m_Ao, context, matDesc.ao);
    }

    MaterialHandle::~MaterialHandle() = default;

    void MaterialHandle::bind() {
        m_Albedo->bind(0);
        m_Normal->bind(1);
        m_Metallic->bind(2);
        m_Roughness->bind(3);
        m_Ao->bind(4);
    }


    GeometryPass::GeometryPass(const RenderData& renderData):
    RenderPass(renderData.context, createGeometryPassFramebufferDesc(renderData.context), GEOMETRY_PASS){
        addDependency(CAMERA_DATA_PASS);
        addDependency(PROJECTION_DATA_PASS);
        addDependency(LINEAR_FILTER_WRAP_REPEAT_SAMPLER_PASS);

        m_VertexDescription->addAttribute("Position", SR_FLOAT32_3);
        m_VertexDescription->addAttribute("Normal", SR_FLOAT32_3);
        m_VertexDescription->addAttribute("Tangent", SR_FLOAT32_3);
        m_VertexDescription->addAttribute("TexCoords", SR_FLOAT32_2);

        auto package = renderData.shaderLibrary->getPackage("GeometryPass");
        m_VertexShaderModule = package.vertexShader;
        m_Shader = m_Context->createShader(package);

        ConstantBufferDesc cbDesc;
        cbDesc.name = "ModelData";
        cbDesc.size = sizeof(MeshTransformation) * MAX_INSTANCES;
        cbDesc.slot = 2;
        cbDesc.type = SR_BUFFER_DYNAMIC;
        cbDesc.shaderStage = SR_SHADER_VERTEX;
        MeshTransformation defaultData[MAX_INSTANCES];
        cbDesc.data = &defaultData;
        m_ModelData = m_Context->createConstantBuffer(cbDesc);

        MaterialDesc defaultMaterial;
        m_Materials.emplace(0, m_Context, defaultMaterial);
    }

    GeometryPass::~GeometryPass() {

    }

    void GeometryPass::execute() {
        m_Context->beginRenderPass(m_FrameBuffer);

        m_ModelData->bind();
        m_Shader->bind();
        for (const auto& mesh: m_Meshes){
            const auto& transformations = mesh.getTransformations();
            m_ModelData->setData(transformations.data());
            m_Materials[mesh.materialID].bind();
            m_Context->drawInstanced(mesh.getVertexArray(), mesh.getInstanceCount());
        }
        m_Context->endRenderPass(m_FrameBuffer);
    }


    InstanceID GeometryPass::createNewInstance(const MeshDesc &meshDesc) {
        // create mesh information
        MeshID mid = generateID();
        m_Meshes.emplace(mid, m_Context, meshDesc, m_VertexShaderModule, m_VertexDescription);

        // create Instance
        InstanceID iid =  m_Meshes[mid].createNewInstance();
        m_Instances.emplace(iid, mid);
        return iid;
    }

    InstanceID GeometryPass::createNewInstanceFromOther(InstanceID otherInstance) {
        SR_PRECONDITION(m_Instances.find(otherInstance) != m_Instances.end(), SR_MESSAGE_RENDERER, "Instance %d does not exist", otherInstance);

        MeshID mid = m_Instances[otherInstance];

        InstanceID iid =  m_Meshes[mid].createNewInstance();
        m_Instances.emplace(iid, mid);
        return iid;
    }

    void GeometryPass::setTransformation(InstanceID instanceId, const glm::mat4 &modelMatrix) {
        SR_PRECONDITION(m_Instances.find(instanceId) != m_Instances.end(), SR_MESSAGE_RENDERER, "Instance %d does not exist", instanceId);

        m_Meshes[m_Instances[instanceId]].setTransformation(instanceId, modelMatrix);
    }

    void GeometryPass::removeInstance(InstanceID instanceId) {
        SR_PRECONDITION(m_Instances.find(instanceId) != m_Instances.end(), SR_MESSAGE_RENDERER, "Instance %d does not exist", instanceId);

        MeshID mid = m_Instances[instanceId]; // get the mesh id, we need to modify the mesh
        m_Instances.erase(instanceId); // remove the instance

        auto& handle = m_Meshes[mid]; // get the mesh handle
        handle.removeInstance(instanceId); // remove the instance from the mesh

        if (handle.getInstanceCount() == 0){ // if there are no more instances using the mesh, remove the mesh
            m_Meshes.remove(mid);
        }
    }

    MaterialID GeometryPass::createMaterial(const MaterialDesc &matDesc) {
        MaterialID materialID = generateID();
        m_Materials.emplace(materialID, m_Context, matDesc);
        return materialID;
    }

    void GeometryPass::instanceSetMaterial(InstanceID instanceId, MaterialID materialID) {
        SR_PRECONDITION(m_Instances.find(instanceId) != m_Instances.end(), SR_MESSAGE_RENDERER, "Instance %d does not exist", instanceId);

        auto& handle = m_Meshes[m_Instances[instanceId]];
        handle.materialID = materialID;
    }

    void GeometryPass::removeMaterial(MaterialID materialID) {
        for (auto& data: m_Meshes){
            if (data.materialID == materialID){ //prevent that existing meshes are still using the material, just fall back to the default material
                data.materialID = 0;
            }
        }
        m_Materials.remove(materialID);
    }

}