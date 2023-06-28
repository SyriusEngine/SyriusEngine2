#include "../../../../include/SyriusEngine/ECS/MeshComponent.hpp"
#include "../../Renderer/PBRenderLayer/PBRenderLayer.hpp"

namespace Syrius{

    MeshComponent::MeshComponent(const MeshDesc &desc, RCP<PBRenderLayer> &renderLayer):
    ModelComponent(renderLayer),
    m_InstanceID(renderLayer->createNewInstance(desc)){

    }

    MeshComponent::MeshComponent(InstanceID otherInstance, RCP<PBRenderLayer> &renderLayer):
    ModelComponent(renderLayer),
    m_InstanceID(renderLayer->createNewInstanceFromOther(otherInstance)){

    }

    MeshComponent::~MeshComponent() {
        printf("MeshComponent destructor not implemented correctly\n");
//        m_RenderLayer->removeInstance(m_InstanceID);
//        m_InstanceID = 0;
    }

    void MeshComponent::setTransformation(const glm::mat4 &transformation) {
        ModelComponent::setTransformation(transformation);
        m_RenderLayer->setTransformation(m_InstanceID, transformation);
    }

    void MeshComponent::setMaterial(MaterialID materialID) {
        m_RenderLayer->instanceSetMaterial(m_InstanceID, materialID);
        ModelComponent::setMaterial(materialID);
    }

    InstanceID MeshComponent::getInstanceID() const {
        return m_InstanceID;
    }

    void MeshComponent::destroy() {
        m_RenderLayer->removeInstance(m_InstanceID);
        m_InstanceID = 0;
        ModelComponent::destroy();
    }

}
