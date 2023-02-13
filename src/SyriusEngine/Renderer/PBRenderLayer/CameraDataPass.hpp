#pragma once

#include "ResourcePass.hpp"

namespace Syrius{

    class CameraDataPass : public ResourcePass{
    public:
        explicit CameraDataPass(ResourceView<Context>& context);

        ~CameraDataPass() override;

        void setCameraData(const glm::mat4 &viewMat, const glm::vec3 &camPos);

    };

}

