#pragma once

#include "RenderPass.hpp"

namespace Syrius {

    struct MeshDesc {
        std::vector<Vertex> vertices;
        std::vector<uint32> indices;
        MaterialID materialID = 0;
    };

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

    class GeometryPass : public RenderPass {
    public:
        GeometryPass(ResourceView<Context> &context, UP<ShaderLibrary>& shaderLibrary);

        ~GeometryPass() override;

        void execute() override;

        MeshID createMesh(const MeshDesc& meshDesc);

        void setMeshTransformation(MeshID mid, const glm::mat4& modelMatrix);

        void removeMesh(MeshID mid);

    private:
        KeyVector<MeshID, MeshHandle> m_Meshes;

        ResourceView<ShaderModule> m_VertexShaderModule;
        ResourceView<ConstantBuffer> m_ModelData;
    };

}