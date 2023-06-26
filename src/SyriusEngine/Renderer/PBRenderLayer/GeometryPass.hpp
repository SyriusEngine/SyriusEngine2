#pragma once

#include "RenderPass.hpp"

namespace Syrius {

    struct MeshTransformation {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 normalMatrix = glm::mat4(1.0f);
    };

    struct MeshHandle {
        ResourceView<VertexBuffer> vertexBuffer;
        ResourceView<IndexBuffer> indexBuffer;
        ResourceView<VertexArray> vertexArray;
        KeyVector<InstanceID, MeshTransformation> transformations = KeyVector<InstanceID, MeshTransformation>(MAX_INSTANCES);
        MaterialID materialID = 0;
    };

    class MaterialHandle{
    public:
        MaterialHandle(ResourceView<Context>& context, const MaterialDesc& matDesc);

        ~MaterialHandle();

        void bind();

    private:
        ResourceView<Texture2D> m_Albedo;
        ResourceView<Texture2D> m_Normal;
        ResourceView<Texture2D> m_Metallic;
        ResourceView<Texture2D> m_Roughness;
        ResourceView<Texture2D> m_Ao;

    };

    class GeometryPass : public RenderPass {
    public:
        explicit GeometryPass(const RenderData& renderData);

        ~GeometryPass() override;

        void execute() override;

        InstanceID createNewInstance(const MeshDesc& meshDesc);

        InstanceID createNewInstanceFromOther(InstanceID otherInstance);

        void setTransformation(InstanceID instanceId, const glm::mat4& modelMatrix);

        void removeInstance(InstanceID instanceId);

        MaterialID createMaterial(const MaterialDesc& matDesc);

        void instanceSetMaterial(InstanceID instanceId, MaterialID materialID);

        void removeMaterial(MaterialID materialID);

    private:
        KeyVector<MeshID, MeshHandle> m_Meshes;
        KeyVector<MaterialID, MaterialHandle> m_Materials;
        std::unordered_map<InstanceID, MeshID> m_Instances; // used to access actual mesh information from instanceID

        ResourceView<ShaderModule> m_VertexShaderModule;
        ResourceView<ConstantBuffer> m_ModelData;
    };

}