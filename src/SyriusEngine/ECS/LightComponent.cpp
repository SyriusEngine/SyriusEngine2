#include "../../../include/SyriusEngine/ECS/LightComponent.hpp"
#include "../Renderer/PBRenderLayer/PBRenderLayer.hpp"

namespace Syrius{

    LightComponent::LightComponent(const LightDesc &lightDesc, RCP<PBRenderLayer> &renderLayer):
    m_RenderLayer(renderLayer),
    m_Position(lightDesc.position),
    m_Color(lightDesc.color),
    m_LightID(renderLayer->createLight(lightDesc)){

    }

    LightComponent::~LightComponent() {
        m_RenderLayer->removeLight(m_LightID);
        m_LightID = 0;
    }

    void LightComponent::setPosition(const glm::vec3 &position) {
        m_Position = position;
        printf("CHANGE LIGHTPOS NOT IMPLEMENTED YET");
    }

    void LightComponent::setColor(const glm::vec3 &color) {
        m_Color = color;
    }

    const glm::vec3 &LightComponent::getPosition() const {
        return m_Position;
    }

    const glm::vec3 &LightComponent::getColor() const {
        return m_Color;
    }
}
