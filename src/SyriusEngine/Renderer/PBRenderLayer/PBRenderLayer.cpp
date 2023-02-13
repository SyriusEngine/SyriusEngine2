#include "PBRenderLayer.hpp"

namespace Syrius{

    PBRenderLayer::PBRenderLayer(const UP<RenderContext> &renderContext) :
    RenderLayer(renderContext) {

    }

    PBRenderLayer::~PBRenderLayer() {

    }

    void PBRenderLayer::onAttach() {
        m_RenderThread.pushTaskSync([this]{
            m_CameraDataPass = createRCP<CameraDataPass>(m_Context);

            ProjectionDesc prDesc;
            prDesc.m_Width = static_cast<float>(m_Context->getWidth());
            prDesc.m_Height = static_cast<float>(m_Context->getHeight());
            m_ProjectionPass = createRCP<ProjectionPass>(m_Context, prDesc);

            m_GeometryPass = createRCP<GeometryPass>(m_Context, m_ShaderLibrary);

            m_GeometryPass->addInput(m_ProjectionPass);
            m_GeometryPass->addInput(m_CameraDataPass);
        });
    }

    void PBRenderLayer::onDetach() {
        m_RenderThread.pushTaskSync([this]{
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
                m_GeometryPass->onResize(newWidth, newHeight);
                //// HANDLE RESIZE (framebuffers and projection)
            });
        }
        return true;
    }

    ResourceView<FrameBuffer> &PBRenderLayer::onRender(ResourceView<FrameBuffer> &framebuffer) {
        m_GeometryPass->execute();
        return m_GeometryPass->getFrameBuffer();
    }

    MeshID PBRenderLayer::createMesh(const MeshDesc &desc) {
        MeshID meshID = 0;
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
}