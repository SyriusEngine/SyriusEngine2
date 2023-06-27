#pragma once

#include "include/SyriusEngine/SyriusEngine.hpp"

using namespace Syrius;

class ApplicationLayer: public RenderLayer{
public:
    explicit ApplicationLayer(UP<SyriusEngine>& engine);

    ~ApplicationLayer() override;

    void onAttach() override;

    void onDetach() override;

    void onUpdate() override;

    bool onEvent(const Event& event) override;

    ResourceView<FrameBuffer>& onRender(ResourceView<FrameBuffer>& framebuffer) override;

private:

    void onAttachSphere();

    void onAttachBackpackGuitar();

    void onAttachPbrSpheres();

    void onAttachPbrInstancedSpheres();

private:

    UP<SyriusEngine>& m_Engine;

    double m_DeltaTime;
    double m_LastFrameTime;


    EntityID m_Player;
    EntityID m_Model;
    std::vector<EntityID> m_Models;
    bool m_UseCamera = false;
};
