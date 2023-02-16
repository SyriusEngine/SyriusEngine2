#include "../../include/SyriusEngine/Renderer/Primitives.hpp"

namespace Syrius{

    Vertex::Vertex():
    position(0.0f, 0.0f, 0.0f),
    normal(1.0f, 0.0f, 0.0f),
    tangent(0.0f, 1.0f, 0.0f),
    texCoord(0.0f, 0.0f){

    }

    Vertex::Vertex(const glm::vec3 &position,
                   const glm::vec3 &normal,
                   const glm::vec3 &tangent,
                   const glm::vec2 &texCoord):
                   position(position),
                   normal(normal),
                   tangent(tangent),
                   texCoord(texCoord){

    }

    MaterialDesc::MaterialDesc() {
        ubyte colorVec[] = {162, 25, 255, 255, 1, 50, 32, 255,
                           1, 50, 32, 255, 162, 25, 255, 255};
        ubyte normalVec[] = {255, 0, 0, 255};
        ubyte zeroVec[] = {0, 0, 0, 255};
        albedo = createImage(colorVec, 1, 1, 4);
        normal = createImage(normalVec, 1, 1, 4);
        metallic = createImage(zeroVec, 1, 1, 4);
        roughness = createImage(zeroVec, 1, 1, 4);
        ao = createImage(zeroVec, 1, 1, 4);
    }

    MaterialDesc::MaterialDesc(const std::string &albedoPath, const std::string &normalPath,
                               const std::string &metallicPath, const std::string &roughnessPath,
                               const std::string &aoPath) {
        albedo = createImage(albedoPath);
        normal = createImage(normalPath);
        metallic = createImage(metallicPath);
        roughness = createImage(roughnessPath);
        ao = createImage(aoPath);
    }
}

