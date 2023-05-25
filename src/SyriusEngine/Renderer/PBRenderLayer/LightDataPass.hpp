#pragma once

#include "ResourcePass.hpp"

namespace Syrius{

    struct LightData{
        glm::vec4 m_Position[300];
        glm::vec4 m_Color[300];
        glm::ivec4 m_LightCount = {0, 0, 0, 0}; // D3D11 expects constant buffer data to be aligned at a 16 byte boundary
    };

    class LightDataPass: public ResourcePass{
    public:
        explicit LightDataPass(ResourceView<Context>& context);

        ~LightDataPass() override;

        LightID createLight(const LightDesc& desc);

        void removeLight(LightID index);

    private:
        LightData m_LightData;
        std::unordered_map<LightID, Index> m_KeyLightMap;
        Index m_LightCount;
    };

}