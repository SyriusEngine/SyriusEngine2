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
        // really fucking stupid but vector resizing also calls destructors. We do not want a lightcomponent to remove
        // the reference inside the renderer just because some vector decided to resize.

        printf("LightComponent destructor not implemented correctly\n");
    }

    void LightComponent::destroy() {
        m_RenderLayer->removeLight(m_LightID);
        m_LightID = 0;
    }

    void LightComponent::setPosition(const glm::vec3 &position) {
        m_Position = position;
        m_RenderLayer->setLightPosition(m_LightID, position);
    }

    void LightComponent::setColor(const glm::vec3 &color) {
        m_Color = color;
        m_RenderLayer->setLightColor(m_LightID, color);
    }

    const glm::vec3 &LightComponent::getPosition() const {
        return m_Position;
    }

    const glm::vec3 &LightComponent::getColor() const {
        return m_Color;
    }

}
