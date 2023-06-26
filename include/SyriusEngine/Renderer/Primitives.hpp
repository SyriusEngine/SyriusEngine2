#pragma once

#include "../Include.hpp"
#include "../Debug.hpp"
#include "../Utils/KeyVector.hpp"

namespace Syrius{

    typedef UID MeshID;
    typedef UID LightID;
    typedef UID MaterialID;
    typedef UID InstanceID;

    const uint64 MAX_INSTANCES = 100;

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

    struct MeshDesc {
        std::vector<Vertex> vertices;
        std::vector<uint32> indices;
        MaterialID materialID = 0;
    };

    struct SR_API MaterialDesc{
        Resource<Image> albedo;
        Resource<Image> normal;
        Resource<Image> metallic;
        Resource<Image> roughness;
        Resource<Image> ao;

        MaterialDesc();

        explicit MaterialDesc(const std::string& albedoPath, const std::string& normalPath = "", const std::string& metallicPath = "", const std::string& roughnessPath = "", const std::string& aoPath = "");

        MaterialDesc(Resource<Image> albedo, Resource<Image> normal, Resource<Image> metallic, Resource<Image> roughness, Resource<Image> ao);

    };

    struct SR_API LightDesc{
        glm::vec3 position;
        glm::vec3 color;
    };

}