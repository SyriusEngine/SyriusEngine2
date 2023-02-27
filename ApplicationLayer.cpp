#include "ApplicationLayer.hpp"

ApplicationLayer::ApplicationLayer(UP<SyriusEngine> &engine):
m_Engine(engine),
m_Player(0),
m_DeltaTime(1.0f),
m_LastFrameTime(0.0f){

}

ApplicationLayer::~ApplicationLayer() {

}

void ApplicationLayer::onAttach() {
    m_Player = m_Engine->createEntity();
    m_Engine->addCameraComponent(m_Player, 0.2f, .01f);

    MaterialDesc matDesc("./Resources/Textures/RustedIron/rustediron2_basecolor.png",
                         "./Resources/Textures/RustedIron/rustediron2_normal.png",
                         "./Resources/Textures/RustedIron/rustediron2_metallic.png",
                         "./Resources/Textures/RustedIron/rustediron2_roughness.png");
    auto chippedPaintMetal = m_Engine->createMaterial(matDesc);

    m_Model = m_Engine->createEntity();
    m_Engine->addModelComponent(m_Model);
    auto& modelComp = m_Engine->getModelComponent(m_Model);
    modelComp.addCube();
    modelComp.setMaterial(chippedPaintMetal);
    modelComp.setTranslate({0.0f, 0.0f, 2.0f});

    auto light1 = m_Engine->createEntity();
    LightDesc l1Desc;
    l1Desc.position = {0.0f, 3.0f, 0.0f};
    l1Desc.color = {255.0f, 255.0f, 255.0f};
    m_Engine->addLightComponent(light1, l1Desc);

}

void ApplicationLayer::onDetach() {

}

void ApplicationLayer::onUpdate() {
    auto currentTime = static_cast<double>(getTimeMilli());
    m_DeltaTime = currentTime - m_LastFrameTime;
    m_LastFrameTime = currentTime;
}

bool ApplicationLayer::onEvent(const Event &event) {
    if (event.type == SR_EVENT_KEYBOARD_KEY_PRESSED){
        if (event.keyCode == SR_KEY_ESCAPE){
            if (!m_UseCamera){
                m_UseCamera = true;
                m_Engine->getInternalWindow()->grabMouse();
                m_Engine->getInternalWindow()->hideMouse();
            }
            else{
                m_UseCamera = false;
                m_Engine->getInternalWindow()->releaseMouse();
                m_Engine->getInternalWindow()->showMouse();
            }
        }
    }
    if (m_UseCamera){
        if (event.type == SR_EVENT_RAW_MOUSE_MOVED){
            auto& camera = m_Engine->getCameraComponent(m_Player);
            camera.updateRaw(event.mousePosX, event.mousePosY);
        }
        else if (event.type == SR_EVENT_KEYBOARD_KEY_PRESSED){
            auto& camera = m_Engine->getCameraComponent(m_Player);
            if (event.keyCode == SR_KEY_W){
                camera.moveForward(m_DeltaTime);
            }
            else if (event.keyCode == SR_KEY_S){
                camera.moveBackwards(m_DeltaTime);
            }
            else if (event.keyCode == SR_KEY_A){
                camera.moveLeft(m_DeltaTime);
            }
            else if (event.keyCode == SR_KEY_D){
                camera.moveRight(m_DeltaTime);
            }
            else if (event.keyCode == SR_KEY_SPACE){
                camera.moveUp(m_DeltaTime);
            }
            else if (event.keyCode == SR_KEY_C){
                camera.moveDown(m_DeltaTime);
            }
        }
    }

    return true;
}
