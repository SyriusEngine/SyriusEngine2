#pragma once

#include "../../../../include/SyriusEngine/Renderer/RenderLayer.hpp"
#include "CameraDataPass.hpp"
#include "ProjectionDataPass.hpp"
#include "GeometryPass.hpp"
#include "LightPass.hpp"

#include "RenderGraph.hpp"

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

        void setMeshTransformation(MeshID meshID, const glm::mat4& modelMatrix);

        void removeMesh(MeshID meshID);

        void setCameraData(const glm::mat4& view, const glm::vec3& cameraPosition);

        MaterialID createMaterial(const MaterialDesc& matDesc);

        void meshSetMaterial(MeshID meshID, MaterialID materialID);

        void removeMaterial(MaterialID materialID);

        LightID createLight(const LightDesc& lightDesc);

        void removeLight(LightID lightID);

    private:

        RenderGraph m_RenderGraph;

        RCP<ProjectionDataPass> m_ProjectionPass;
        RCP<CameraDataPass> m_CameraDataPass;

        RCP<GeometryPass> m_GeometryPass;
        RCP<LightPass> m_LightPass;

    };

}