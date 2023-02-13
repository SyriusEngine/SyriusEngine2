#pragma once

#include "../Include.hpp"
#include "../Debug.hpp"
#include "../Utils/KeyVector.hpp"

namespace Syrius{

    typedef UID MeshID;
    typedef UID LightID;
    typedef UID MaterialID;
    typedef UID Entry;

    class PBRenderLayer;

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

    struct SR_API Vertex{
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec2 texCoord;

        Vertex();

        Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec3& tangent, const glm::vec2& texCoord);
    };

}