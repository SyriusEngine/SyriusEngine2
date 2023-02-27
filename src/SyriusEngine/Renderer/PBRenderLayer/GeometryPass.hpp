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
        MeshTransformation transformation;
        MaterialID materialID = 0;
    };

    class MaterialHandle{
    public:
        MaterialHandle(ResourceView<Context>& context, const MaterialDesc& matDesc, ResourceView<Sampler>& sampler);

        ~MaterialHandle();

        void bind();

    private:

        void createTexture(ResourceView<Texture2D>& texture, ResourceView<Context>& context, const Resource<Image>& image, ResourceView<Sampler>& sampler);

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

        MeshID createMesh(const MeshDesc& meshDesc);

        void setMeshTransformation(MeshID mid, const glm::mat4& modelMatrix);

        void removeMesh(MeshID mid);

        MaterialID createMaterial(const MaterialDesc& matDesc);

        void meshSetMaterial(MeshID meshID, MaterialID materialID);

        void removeMaterial(MaterialID materialID);

    private:
        KeyVector<MeshID, MeshHandle> m_Meshes;
        KeyVector<MaterialID, MaterialHandle> m_Materials;

        ResourceView<ShaderModule> m_VertexShaderModule;
        ResourceView<ConstantBuffer> m_ModelData;
        ResourceView<Sampler>& m_Sampler;
    };

}