#include "ApplicationLayer.hpp"

ApplicationLayer::ApplicationLayer(UP<SyriusEngine> &engine):
RenderLayer(engine->getRenderContext()),
m_Engine(engine),
m_Player(0),
m_DeltaTime(1.0f),
m_LastFrameTime(0.0f),
m_CreatorThread(){
    m_CreatorThread.start();
}

ApplicationLayer::~ApplicationLayer() {

}

void ApplicationLayer::onAttach() {
    m_RenderThread.pushTask([this]{
       m_Engine->getInternalWindow()->createImGuiContext();
    });
    m_Player = m_Engine->createEntity();
    m_Engine->addCameraComponent(m_Player, 0.2f, .01f);

    //onAttachSphere();
    onAttachPbrInstancedSpheres();

    auto light1 = m_Engine->createEntity();
    LightDesc l1Desc;
    l1Desc.position = {0.0f, 8.0f, 1.0f};
    l1Desc.color = {255.0f, 255.0f, 255.0f};
    m_Engine->addLightComponent(light1, l1Desc);
    m_Lights.push_back(light1);

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
    framebuffer->bind();
    m_Engine->getInternalWindow()->onImGuiBegin();

    ImGui::Begin("DeBug");

    ImGui::Text("FPS: %f", 1000.0f / m_DeltaTime);

    ImGui::End();

    drawLightPanel();

    m_Engine->getInternalWindow()->onImGuiEnd();
    framebuffer->unbind();
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

}

void ApplicationLayer::onAttachBackpackGuitar() {
    m_Model = m_Engine->createEntity();
    m_Engine->addModelComponent(m_Model, "./Resources/Models/Survival_Backpack_2/Survival_BackPack_2.fbx");
    //m_Engine->addModelComponent(m_Model, "./Resources/Models/Cerberus/Cerberus_LP.fbx");
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

}

void ApplicationLayer::onAttachPbrInstancedSpheres() {
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
    auto sphereInstanceId = sphere->getInstanceID();
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    sphere->setTranslate({x, y, z});

    int numSpheres = 50;
    float cubeSize = 3.0f;
    float spacing = 0.5f;
    int spheresPerCubeSide = 1;
    for (int i = 0; i < numSpheres; ++i) {
        float cubeHalfSize = (cubeSize * spheresPerCubeSide) / 2.0f;
        float sphereSpacing = cubeSize + spacing;
        int currentCubeIndex = i / (spheresPerCubeSide * spheresPerCubeSide);

        float xPos = (i % spheresPerCubeSide) * sphereSpacing;
        float yPos = ((i / spheresPerCubeSide) % spheresPerCubeSide) * sphereSpacing;
        float zPos = currentCubeIndex * sphereSpacing;

        sphere->addSubMesh(sphereInstanceId)->setTranslate({ xPos - cubeHalfSize, yPos - cubeHalfSize, zPos - cubeHalfSize });

        if (i == spheresPerCubeSide * spheresPerCubeSide - 1) {
            spheresPerCubeSide++;
        }
    }

}

void ApplicationLayer::drawLightPanel() {
    ImGui::Begin("Light Panel");

    if (ImGui::Button("Create Light")){
        m_CreatorThread.pushTask([this]{
            auto light1 = m_Engine->createEntity();
            LightDesc l1Desc;
            l1Desc.position = {0.0f, 0.0f, 0.0f};
            l1Desc.color = {255.0f, 255.0f, 255.0f};
            m_Engine->addLightComponent(light1, l1Desc);
            m_Lights.push_back(light1);
        });
    }

    static EntityID selected = 0;
    if (ImGui::BeginListBox("Light IDs")){
        for (auto& light : m_Lights){
            const bool isSelected = (selected == light);
            if (ImGui::Selectable(std::to_string(light).c_str(), isSelected)){
                selected = light;
            }
            if (isSelected){
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndListBox();
    }

    if (selected != 0){
        auto& lightComp = m_Engine->getLightComponent(selected);
        float position[3] = {lightComp.getPosition().x, lightComp.getPosition().y, lightComp.getPosition().z};
        float color[3] = {lightComp.getColor().x, lightComp.getColor().y, lightComp.getColor().z};
        if (ImGui::DragFloat3("Position", position, 0.1f)){
            lightComp.setPosition({position[0], position[1], position[2]});
        }
        if (ImGui::DragFloat3("Color", color, 0.1f)){
            lightComp.setColor({color[0], color[1], color[2]});
        }

        if (ImGui::Button("Delete Light")){
            auto id = selected;
            selected = 0;
            m_CreatorThread.pushTask([this, id]{
                m_Engine->removeLightComponent(id);
                m_Lights.erase(std::remove(m_Lights.begin(), m_Lights.end(), id), m_Lights.end());
                m_Engine->destroyEntity(id);
            });
        }

    }

    ImGui::End();
}
