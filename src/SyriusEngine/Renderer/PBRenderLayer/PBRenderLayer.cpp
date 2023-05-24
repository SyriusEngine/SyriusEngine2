#include "PBRenderLayer.hpp"

namespace Syrius{

    PBRenderLayer::PBRenderLayer(const UP<RenderContext> &renderContext) :
    RenderLayer(renderContext) {

    }

    PBRenderLayer::~PBRenderLayer() {

    }

    void PBRenderLayer::onAttach() {
        m_RenderThread.pushTaskSync([this]{

            RenderData renderData(m_Context, m_DefaultSampler, m_ShaderLibrary);

            m_CameraDataPass = createRCP<CameraDataPass>(m_Context);

            ProjectionDesc prDesc;
            prDesc.m_Width = static_cast<float>(m_Context->getWidth());
            prDesc.m_Height = static_cast<float>(m_Context->getHeight());
            m_ProjectionPass = createRCP<ProjectionDataPass>(m_Context, prDesc);

            m_GeometryPass = createRCP<GeometryPass>(renderData);

            m_GeometryPass->addInput(m_ProjectionPass);
            m_GeometryPass->addInput(m_CameraDataPass);

            m_LightPass = createRCP<LightPass>(renderData, m_GeometryPass);
        });
    }

    void PBRenderLayer::onDetach() {
        m_RenderThread.pushTaskSync([this]{
            m_LightPass.reset();
            m_GeometryPass.reset();

            m_ProjectionPass.reset();
            m_CameraDataPass.reset();
        });
    }

    void PBRenderLayer::onUpdate() {

    }

    bool PBRenderLayer::onEvent(const Event &event) {
        if (event.type == SR_EVENT_WINDOW_RESIZED){
            auto newWidth = event.windowWidth;
            auto newHeight = event.windowHeight;
            m_RenderThread.pushTask([newWidth, newHeight, this]{

                m_ProjectionPass->onResize(newWidth, newHeight);
                m_GeometryPass->onResize(newWidth, newHeight);
            });
        }
        return true;
    }

    ResourceView<FrameBuffer> &PBRenderLayer::onRender(ResourceView<FrameBuffer> &framebuffer) {
        m_DefaultSampler->bind(0);
        m_LightPass->execute();
        return m_LightPass->getFrameBuffer();
    }

    MeshID PBRenderLayer::createMesh(const MeshDesc &desc) {
        MeshID meshID = 0;
        /*
         * Desc can be taken in via reference because the caller thread will be blocked until the mesh is created.
         * The desc object will not go out of scope.
         */
        m_RenderThread.pushTaskSync([&desc, &meshID, this]{
            meshID = m_GeometryPass->createMesh(desc);
        });
        return meshID;
    }

    void PBRenderLayer::setMeshTransformation(MeshID meshID, const glm::mat4& modelMatrix) {
        m_RenderThread.pushTask([meshID, modelMatrix, this]{
            m_GeometryPass->setMeshTransformation(meshID, modelMatrix);
        });
    }

    void PBRenderLayer::removeMesh(MeshID meshID) {
        m_RenderThread.pushTask([meshID, this]{
            m_GeometryPass->removeMesh(meshID);
        });
    }

    void PBRenderLayer::setCameraData(const glm::mat4 &view, const glm::vec3 &cameraPosition) {
        m_RenderThread.pushTask([view, cameraPosition, this]{
            m_CameraDataPass->setCameraData(view, cameraPosition);
        });
    }

    MaterialID PBRenderLayer::createMaterial(const MaterialDesc &matDesc) {
        MaterialID materialID = 0;
        m_RenderThread.pushTaskSync([&materialID, &matDesc, this]{
            materialID = m_GeometryPass->createMaterial(matDesc);
        });
        return materialID;
    }

    void PBRenderLayer::meshSetMaterial(MeshID meshID, MaterialID materialID) {
        m_RenderThread.pushTaskSync([meshID, materialID, this]{
            m_GeometryPass->meshSetMaterial(meshID, materialID);
        });
    }

    void PBRenderLayer::removeMaterial(MaterialID materialID) {
        m_RenderThread.pushTaskSync([materialID, this]{
            m_GeometryPass->removeMaterial(materialID);
        });
    }

    LightID PBRenderLayer::createLight(const LightDesc &lightDesc) {
        LightID lid = 0;
        m_RenderThread.pushTaskSync([&lightDesc, &lid, this]{
            lid = m_LightPass->createLight(lightDesc);
        });
        return lid;
    }

    void PBRenderLayer::removeLight(LightID lightID) {
        m_RenderThread.pushTaskSync([lightID, this]{
            m_LightPass->removeLight(lightID);
        });
    }
}