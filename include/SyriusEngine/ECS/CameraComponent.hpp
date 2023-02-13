#pragma once

#include "../Renderer/Primitives.hpp"

namespace Syrius{

    class SR_API CameraComponent{
    public:
        CameraComponent(float sensitivity, float speed, RCP<PBRenderLayer>& renderLayer);

        ~CameraComponent();

        void update(float mouseX, float mouseY);

        void updateRaw(float xOffset, float yOffset);

        void moveForward(float deltaTime);

        void moveBackwards(float deltaTime);

        void moveLeft(float deltaTime);

        void moveRight(float deltaTime);

        void moveUp(float deltaTime);

        void moveDown(float deltaTime);

        void setSensitivity(float sensitivity);

        void setSpeed(float speed);

        [[nodiscard]] const glm::vec3 &getPosition() const;

        [[nodiscard]] const glm::vec3 &getFrontDir() const;

        [[nodiscard]] const glm::vec3 &getUpDir() const;

        [[nodiscard]] float getPitch() const;

        [[nodiscard]] float getYaw() const;

        void setPosition(const glm::vec3 &newPosition);

        void reset();

    private:

        void updateCameraVectors();

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;

        glm::mat4 m_ViewMat;

        float m_Yaw;
        float m_Pitch;
        float m_Speed;
        float m_Sensitivity;
        float m_LastX;
        float m_LastY;

        bool m_FirstMouse;

        RCP<PBRenderLayer>& m_RenderLayer;

    };


}
