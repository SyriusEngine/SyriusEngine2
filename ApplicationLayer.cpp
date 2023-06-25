#include "ApplicationLayer.hpp"

ApplicationLayer::ApplicationLayer(UP<SyriusEngine> &engine):
RenderLayer(engine->getRenderContext()),
m_Engine(engine),
m_Player(0),
m_DeltaTime(1.0f),
m_LastFrameTime(0.0f){

}

ApplicationLayer::~ApplicationLayer() {

}

void ApplicationLayer::onAttach() {
    m_RenderThread.pushTask([this]{
       m_Engine->getInternalWindow()->createImGuiContext();
    });
    m_Player = m_Engine->createEntity();
    m_Engine->addCameraComponent(m_Player, 0.2f, .01f);

    onAttachSphere();
    //onAttachBackpackGuitar();
    //onAttachPbrSpheres();

    auto light1 = m_Engine->createEntity();
    LightDesc l1Desc;
    l1Desc.position = {0.0f, 8.0f, 1.0f};
    l1Desc.color = {255.0f, 255.0f, 255.0f};
    m_Engine->addLightComponent(light1, l1Desc);

}

void ApplicationLayer::onDetach() {
    m_RenderThread.pushTask([this]{
        m_Engine->getInternalWindow()->destroyImGuiContext();
    });

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

ResourceView<FrameBuffer> &ApplicationLayer::onRender(ResourceView<FrameBuffer> &framebuffer) {
    m_Engine->getInternalWindow()->onImGuiBegin();

    m_Engine->getInternalWindow()->onImGuiEnd();
    return framebuffer;
}

void ApplicationLayer::onAttachSphere() {
    MaterialDesc ChippedPaintMetalDesc(
            "./Resources/Textures/ChippedPaintMetal/Chipped-paint-metal_basecolor.png",
            "./Resources/Textures/ChippedPaintMetal/Chipped-paint-metal_normal.png",
            "./Resources/Textures/ChippedPaintMetal/Chipped-paint-metal_metallic.png",
            "./Resources/Textures/ChippedPaintMetal/Chipped-paint-metal_roughness.png",
            "./Resources/Textures/ChippedPaintMetal/Chipped-paint-metal_ao.png"
    );
    MaterialID ChippedPaintMetalID = m_Engine->createMaterial(ChippedPaintMetalDesc);

    m_Model = m_Engine->createEntity();
    m_Engine->addModelComponent(m_Model);
    auto sphere = m_Engine->getModelComponent(m_Model).addSphere(32, 32);
    sphere->setMaterial(ChippedPaintMetalID);
    sphere->setTranslate({0.0f, 0.0f, 3.0f});

    auto sphereInstanceId = sphere->getInstanceID();
    auto instSphere = sphere->addSubMesh(sphereInstanceId);
    instSphere->setTranslate({0.0f, 3.0f, 3.0f});
}

void ApplicationLayer::onAttachBackpackGuitar() {
    m_Model = m_Engine->createEntity();
    //m_Engine->addModelComponent(m_Model, "./Resources/Models/Survival_Backpack_2/Survival_BackPack_2.fbx");
    m_Engine->addModelComponent(m_Model, "./Resources/Models/Cerberus/Cerberus_LP.fbx");
    m_Engine->getModelComponent(m_Model).setRotate({0.0f, 0.0f, 0.0f});
    m_Engine->getModelComponent(m_Model).setScale({0.1f, 0.1f, 0.1f});

    MaterialDesc cerberusDesc(
            "./Resources/Models/Cerberus/Cerberus_A.jpg",
            "./Resources/Models/Cerberus/Cerberus_N.jpg",
            "./Resources/Models/Cerberus/Cerberus_M.jpg",
            "./Resources/Models/Cerberus/Cerberus_R.jpg",
            ""
    );
    MaterialID cerberusID = m_Engine->createMaterial(cerberusDesc);
    m_Engine->getModelComponent(m_Model).setMaterial(cerberusID);

}

void ApplicationLayer::onAttachPbrSpheres() {
    uint8 maxX = 7;
    uint8 maxY = 7;

    m_Model = m_Engine->createEntity();
    m_Engine->addModelComponent(m_Model);

    for (uint8 x = 0; x < maxX; x++) {
        for (uint8 y = 0; y < maxY; y++) {
            auto sphere = m_Engine->getModelComponent(m_Model).addSphere(32, 32);

            ubyte semiRed[4] = {255, 0, 0, 255};
            auto albedo = createImage(semiRed, 1, 1, Syrius::SR_TEXTURE_RGBA_UI8);
            ubyte normalVec[4] = {128, 128, 255, 255};
            auto normal = createImage(normalVec, 1, 1, Syrius::SR_TEXTURE_RGBA_UI8);
            ubyte metallicVec[4] = {static_cast<ubyte>(x / maxX), static_cast<ubyte>(x / maxX),
                                    static_cast<ubyte>(x / maxX), 255};
            auto metallic = createImage(metallicVec, 1, 1, Syrius::SR_TEXTURE_RGBA_UI8);
            ubyte roughnessVec[4] = {static_cast<ubyte>(y / maxY), static_cast<ubyte>(y / maxY),
                                     static_cast<ubyte>(y / maxY), 255};
            auto roughness = createImage(roughnessVec, 1, 1, Syrius::SR_TEXTURE_RGBA_UI8);
            ubyte aoVec[4] = {255, 255, 255, 255};
            auto ao = createImage(aoVec, 1, 1, Syrius::SR_TEXTURE_RGBA_UI8);

            MaterialDesc desc(std::move(albedo), std::move(normal), std::move(metallic), std::move(roughness),
                              std::move(ao));
            MaterialID id = m_Engine->createMaterial(desc);
            sphere->setMaterial(id);
            sphere->setTranslate({x * 2, y * 2, 3.0f});
        }
    }

}
