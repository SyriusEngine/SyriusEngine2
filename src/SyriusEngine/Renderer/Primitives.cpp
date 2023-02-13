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

}

