#include "../../../include/SyriusEngine/ECS/CameraComponent.hpp"
#include "../Renderer/PBRenderLayer/PBRenderLayer.hpp"

namespace Syrius{

    CameraComponent::CameraComponent(float sensitivity, float speed, RCP<PBRenderLayer>& renderLayer)
            : m_Sensitivity(sensitivity),
              m_Speed(speed),
              m_Pitch(0.0f),
              m_Yaw(90.0f),
              m_LastX(0.0f),
              m_LastY(0.0f),
              m_FirstMouse(true),
              m_Position({0.0f, 0.0f, 0.0f}),
              m_Up({0.0f, 1.0f, 0.0f}),
              m_Front({0.0f, 0.0f, 1.0f}),
              m_WorldUp({0.0f, 1.0f, 0.0f}),
              m_ViewMat(glm::mat4(1.0f)),
              m_RenderLayer(renderLayer){
        updateCameraVectors();
    }

    CameraComponent::~CameraComponent() {

    }

    void CameraComponent::update(float mouseX, float mouseY) {
        if (m_FirstMouse){
            m_LastX = mouseX;
            m_LastY = mouseY;
            m_FirstMouse = false;
        }
        float xOffset = mouseX - m_LastX;
        float yOffset = m_LastY - mouseY;
        m_LastX = mouseX;
        m_LastY = mouseY;

        xOffset *= m_Sensitivity;
        yOffset *= m_Sensitivity;
        m_Yaw += xOffset;
        m_Pitch += yOffset;
        // when dragged to far, make sure the screen doesn't get flipped
        if (m_Pitch > 89.0f) {
            m_Pitch = 89.0f;
        }
        if (m_Pitch < -89.0f) {
            m_Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void CameraComponent::updateRaw(float xOffset, float yOffset) {
        yOffset = -yOffset;
        xOffset *= m_Sensitivity;
        yOffset *= m_Sensitivity;
        m_Yaw += xOffset;
        m_Pitch += yOffset;
        // when dragged to far, make sure the screen doesn't get flipped
        if (m_Pitch > 89.0f) {
            m_Pitch = 89.0f;
        }
        if (m_Pitch < -89.0f) {
            m_Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void CameraComponent::moveForward(float deltaTime) {
        float velocity = deltaTime * m_Speed;
        m_Position += m_Front * velocity;
        updateCameraVectors();
    }

    void CameraComponent::moveBackwards(float deltaTime) {
        float velocity = deltaTime * m_Speed;
        m_Position -= m_Front * velocity;
        updateCameraVectors();
    }

    void CameraComponent::moveLeft(float deltaTime) {
        float velocity = deltaTime * m_Speed;
        m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
        updateCameraVectors();
    }

    void CameraComponent::moveRight(float deltaTime) {
        float velocity = deltaTime * m_Speed;
        m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * velocity;
        updateCameraVectors();
    }

    void CameraComponent::moveUp(float deltaTime) {
        float velocity = deltaTime * m_Speed;
        m_Position += m_Up * velocity;
        updateCameraVectors();
    }

    void CameraComponent::moveDown(float deltaTime) {
        float velocity = deltaTime * m_Speed;
        m_Position -= m_Up * velocity;
        updateCameraVectors();
    }

    void CameraComponent::setSensitivity(float sensitivity) {
        m_Sensitivity = sensitivity;
    }

    void CameraComponent::setSpeed(float speed) {
        m_Speed = speed;
    }

    const glm::vec3 &CameraComponent::getPosition() const {
        return m_Position;
    }

    const glm::vec3 &CameraComponent::getFrontDir() const {
        return m_Front;
    }

    const glm::vec3 &CameraComponent::getUpDir() const {
        return m_Up;
    }

    float CameraComponent::getPitch() const {
        return m_Pitch;
    }

    float CameraComponent::getYaw() const {
        return m_Yaw;
    }

    void CameraComponent::setPosition(const glm::vec3 &newPosition) {
        m_Position = newPosition;
        updateCameraVectors();
    }

    void CameraComponent::reset() {
        m_Pitch = 0.0f;
        m_Yaw = 90.0f;
        m_Front = glm::vec3(0.0f, 0.0f, 1.0f);
        m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
        m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        updateCameraVectors();
    }

    void CameraComponent::updateCameraVectors() {
        glm::vec3 front;
        front.x = glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
        front.y = glm::sin(glm::radians(m_Pitch));
        front.z = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));

        m_Front = glm::normalize(front);
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));

        m_ViewMat = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        m_RenderLayer->setCameraData(m_ViewMat, m_Position);
    }

}