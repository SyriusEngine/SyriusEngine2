#include "MeshHandle.hpp"
#include <csignal>

namespace Syrius{

    MeshTransformation::MeshTransformation():
    modelMatrix(glm::mat4(1.0f)),
    normalMatrix(glm::mat4(1.0f)){

    }

    MeshHandle::MeshHandle(ResourceView<Context>& context, const MeshDesc& meshDesc, ResourceView<ShaderModule>& vertexShader, ResourceView<VertexDescription>& vertexDesc):
    materialID(meshDesc.materialID){
        VertexBufferDesc vbDesc;
        vbDesc.data = meshDesc.vertices.data();
        vbDesc.count = meshDesc.vertices.size();
        vbDesc.layout = vertexDesc;
        vbDesc.type = SR_BUFFER_STATIC;
        m_VertexBuffer = context->createVertexBuffer(vbDesc);

        IndexBufferDesc ibDesc;
        ibDesc.data = meshDesc.indices.data();
        ibDesc.count = meshDesc.indices.size();
        ibDesc.type = SR_BUFFER_STATIC;
        ibDesc.dataType = SR_UINT32;
        m_IndexBuffer = context->createIndexBuffer(ibDesc);

        VertexArrayDesc vaDesc;
        vaDesc.vertexBuffer = m_VertexBuffer;
        vaDesc.indexBuffer = m_IndexBuffer;
        vaDesc.vertexShader = vertexShader;
        m_VertexArray = context->createVertexArray(vaDesc);

    }

    MeshHandle::~MeshHandle() {

    }

    InstanceID MeshHandle::createNewInstance() {
        SR_PRECONDITION(m_Transformations.size() < MAX_INSTANCES, SR_MESSAGE_RENDERER, "Cannot create more instances than %d", MAX_INSTANCES);

        InstanceID iid = generateID();
        m_Transformations.emplace_back();
        m_InstanceToIndex.insert({iid, m_Transformations.size() - 1});
        return iid;
    }

    void MeshHandle::setTransformation(InstanceID instanceId, const glm::mat4 &modelMatrix) {
        SR_PRECONDITION(m_InstanceToIndex.find(instanceId) != m_InstanceToIndex.end(), SR_MESSAGE_RENDERER, "Instance %d does not exist", instanceId);

        m_Transformations[m_InstanceToIndex[instanceId]].modelMatrix = modelMatrix;
        m_Transformations[m_InstanceToIndex[instanceId]].normalMatrix = glm::transpose(glm::inverse(modelMatrix));
    }

    void MeshHandle::removeInstance(InstanceID instanceId) {
        // switch last element with the one to be removed
        auto lastDataIndex = m_Transformations.size() - 1;
        auto currentDataIndex = m_InstanceToIndex[instanceId];
        InstanceID lastElementKey;
        for (const auto& lastKey : m_InstanceToIndex){
            if (lastDataIndex == lastKey.second){
                lastElementKey = lastKey.first;
                break;
            }
        }
        // switch last and current element from place
        m_Transformations[currentDataIndex] = std::move(m_Transformations[lastDataIndex]);
        m_Transformations.pop_back();
        m_InstanceToIndex.erase(instanceId);
        // update index
        m_InstanceToIndex[lastElementKey] = currentDataIndex;


    }
}
