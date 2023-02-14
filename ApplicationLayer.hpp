#pragma once

#include "include/SyriusEngine/SyriusEngine.hpp"

using namespace Syrius;

class ApplicationLayer: public Layer{
public:
    explicit ApplicationLayer(UP<SyriusEngine>& engine);

    ~ApplicationLayer() override;

    void onAttach() override;

    void onDetach() override;

    void onUpdate() override;

    bool onEvent(const Event& event) override;

private:
    UP<SyriusEngine>& m_Engine;

    double m_DeltaTime;
    double m_LastFrameTime;

    EntityID m_Player;
    EntityID m_Model;
    bool m_UseCamera = false;
};
