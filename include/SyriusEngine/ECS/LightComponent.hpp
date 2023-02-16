#pragma once

#include "../Renderer/Primitives.hpp"

namespace Syrius{

    class SR_API LightComponent{
    public:
        LightComponent(const LightDesc& lightDesc, RCP<PBRenderLayer>& renderLayer);

        ~LightComponent();

        void setPosition(const glm::vec3& position);

        void setColor(const glm::vec3& color);

        [[nodiscard]] const glm::vec3& getPosition() const;

        [[nodiscard]] const glm::vec3& getColor() const;

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Color;
        LightID m_LightID;

        RCP<PBRenderLayer>& m_RenderLayer;
    };
}