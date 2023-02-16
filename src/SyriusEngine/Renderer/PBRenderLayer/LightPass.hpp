#pragma once

#include "RenderPass.hpp"
#include "GeometryPass.hpp"

namespace Syrius{

    struct LightData{
        glm::vec4 m_Position[300];
        glm::vec4 m_Color[300];
        glm::ivec4 m_LightCount = {0, 0, 0, 0}; // D3D11 expects constant buffer data to be aligned at a 16 byte boundary
    };

    class LightPass : public RenderPass{
    public:
        explicit LightPass(ResourceView<Context>& context, UP<ShaderLibrary> &shaderLibrary, RCP<GeometryPass>& geometryPass);

        ~LightPass() override;

        void execute() override;

        LightID createLight(const LightDesc& desc);

        void removeLight(LightID index);

    private:
        ResourceView<VertexArray> m_ScreenVAO;
        ResourceView<VertexBuffer> m_ScreenVBO;
        ResourceView<IndexBuffer> m_ScreenIBO;
        ResourceView<Sampler> m_Sampler;
        ResourceView<ConstantBuffer> m_LightDataBuffer;

        LightData m_LightData;
        std::unordered_map<LightID, Index> m_KeyLightMap;
        Index m_LightCount;

        RCP<GeometryPass>& m_GeometryPass;
    };

}