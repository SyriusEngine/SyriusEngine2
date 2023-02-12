#pragma once

#include "../Include.hpp"

namespace Syrius{

    typedef UID MeshID;
    typedef UID LightID;
    typedef UID MaterialID;

    class Renderer;

    static glm::vec2 s_ScreenVertices[] = {
            {-1.0f, -1.0f}, {0.0f, 0.0f},
            {1.0f, -1.0f}, {1.0f, 0.0f},
            {1.0f, 1.0f}, {1.0f, 1.0f},
            {-1.0f, 1.0f}, {0.0f, 1.0f}
    };

    static uint32 s_ScreenIndices[] = {
            0, 3, 2,
            0, 2, 1
    };

}