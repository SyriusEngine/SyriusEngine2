#pragma once

#include "../../../include/SyriusEngine/Renderer/Primitives.hpp"

namespace Syrius{

    struct MeshTransformation {
        glm::mat4 modelMatrix;
        glm::mat4 normalMatrix;

        MeshTransformation();
    };

    class MeshHandle {
    public:
        MeshHandle(ResourceView<Context>& context, const MeshDesc& meshDesc, ResourceView<ShaderModule>& vertexShader, ResourceView<VertexDescription>& vertexDesc);

        ~MeshHandle();

        InstanceID createNewInstance();

        void setTransformation(InstanceID instanceId, const glm::mat4& modelMatrix);

        void removeInstance(InstanceID instanceId);

        inline const ResourceView<VertexArray>& getVertexArray() const { return m_VertexArray; }

        inline const std::vector<MeshTransformation>& getTransformations() const { return m_Transformations; }

        inline uint64 getInstanceCount() const { return m_Transformations.size(); }

    public:
        MaterialID materialID;

    private:
        ResourceView<VertexBuffer> m_VertexBuffer;
        ResourceView<IndexBuffer> m_IndexBuffer;
        ResourceView<VertexArray> m_VertexArray;
        std::vector<MeshTransformation> m_Transformations;

        std::unordered_map<InstanceID, uint32_t> m_InstanceToIndex;
    };

}