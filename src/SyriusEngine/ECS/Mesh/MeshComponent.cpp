#include "MeshComponent.hpp"
#include "../../Renderer/PBRenderLayer/PBRenderLayer.hpp"

namespace Syrius{

    MeshComponent::MeshComponent(const MeshDesc &desc, RCP<PBRenderLayer> &renderLayer):
            ModelComponent(renderLayer),
            m_InstanceID(renderLayer->createNewInstance(desc)){

    }

    MeshComponent::~MeshComponent() {
        m_RenderLayer->removeInstance(m_InstanceID);
        m_InstanceID = 0;
    }

    void MeshComponent::setTransformation(const glm::mat4 &transformation) {
        ModelComponent::setTransformation(transformation);
        m_RenderLayer->setTransformation(m_InstanceID, transformation);
    }

    void MeshComponent::setMaterial(MaterialID materialID) {
        m_RenderLayer->instanceSetMaterial(m_InstanceID, materialID);
        ModelComponent::setMaterial(materialID);
    }

}
