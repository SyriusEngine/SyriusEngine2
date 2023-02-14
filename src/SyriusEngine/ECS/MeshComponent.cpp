#include "MeshComponent.hpp"
#include "../Renderer/PBRenderLayer/PBRenderLayer.hpp"

namespace Syrius{

    MeshComponent::MeshComponent(const MeshDesc &desc, RCP<PBRenderLayer> &renderLayer):
    ModelComponent(renderLayer),
    m_MeshID(renderLayer->createMesh(desc)){

    }

    MeshComponent::~MeshComponent() {
        m_RenderLayer->removeMesh(m_MeshID);
        m_MeshID = 0;
    }

    void MeshComponent::setTransformation(const glm::mat4 &transformation) {
        ModelComponent::setTransformation(transformation);
        m_RenderLayer->setMeshTransformation(m_MeshID, transformation);
    }

}
