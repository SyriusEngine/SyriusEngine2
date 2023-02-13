#pragma once

#include "../../../../include/SyriusEngine/Renderer/RenderLayer.hpp"
#include "CameraDataPass.hpp"
#include "ProjectionPass.hpp"
#include "GeometryPass.hpp"

namespace Syrius{

    class PBRenderLayer: public RenderLayer{
    public:
        explicit PBRenderLayer(const UP<RenderContext>& renderContext);

        ~PBRenderLayer() override;

        void onAttach() override;

        void onDetach() override;

        void onUpdate() override;

        bool onEvent(const Event& event) override;

        ResourceView<FrameBuffer>& onRender(ResourceView<FrameBuffer>& framebuffer) override;

        MeshID createMesh(const MeshDesc& desc);

    private:
        RCP<ProjectionPass> m_ProjectionPass;
        RCP<CameraDataPass> m_CameraDataPass;

        RCP<GeometryPass> m_GeometryPass;

    };

}