#pragma once

#include "RenderPass.hpp"
#include "GeometryPass.hpp"

namespace Syrius{

    class LightPass : public RenderPass{
    public:
        explicit LightPass(const RenderData& renderData, RCP<GeometryPass>& geometryPass);

        ~LightPass() override;

        void execute() override;

    private:
        ResourceView<VertexArray> m_ScreenVAO;
        ResourceView<VertexBuffer> m_ScreenVBO;
        ResourceView<IndexBuffer> m_ScreenIBO;

        RCP<GeometryPass>& m_GeometryPass;
    };

}