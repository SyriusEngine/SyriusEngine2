#include "PBRenderLayer.hpp"

namespace Syrius{

    PBRenderLayer::PBRenderLayer(const UP<RenderContext> &renderContext) :
    RenderLayer(renderContext),
    m_RenderGraph(){

    }

    PBRenderLayer::~PBRenderLayer() {

    }

    void PBRenderLayer::onAttach() {
        m_RenderThread.pushTaskSync([this]{
            m_CameraDataPass = createRCP<CameraDataPass>(m_Context);
            m_LightDataPass = createRCP<LightDataPass>(m_Context);
            m_SamplerPass = createRCP<LinearFilterWrapRepeatSamplerPass>(m_Context);

            ProjectionDesc prDesc;
            prDesc.m_Width = static_cast<float>(m_Context->getWidth());
            prDesc.m_Height = static_cast<float>(m_Context->getHeight());
            m_ProjectionPass = createRCP<ProjectionDataPass>(m_Context, prDesc);

            RenderData renderData(m_Context, m_ShaderLibrary);
            m_GeometryPass = createRCP<GeometryPass>(renderData);
            m_LightPass = createRCP<LightPass>(renderData, m_GeometryPass);

            m_RenderGraph.addPass(m_ProjectionPass->getPassDesc());
            m_RenderGraph.addPass(m_LightPass->getPassDesc());
            m_RenderGraph.addPass(m_CameraDataPass->getPassDesc());
            m_RenderGraph.addPass(m_GeometryPass->getPassDesc());
            m_RenderGraph.addPass(m_LightDataPass->getPassDesc());
            m_RenderGraph.addPass(m_SamplerPass->getPassDesc());

            m_RenderGraph.validate();
            m_RenderGraph.compile();
        });
    }

    void PBRenderLayer::onDetach() {
        m_RenderThread.pushTaskSync([this]{
            m_LightPass.reset();
            m_GeometryPass.reset();
            m_SamplerPass.reset();
            m_LightDataPass.reset();

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
        m_RenderGraph.execute();
        return m_LightPass->getFrameBuffer();
    }

    InstanceID PBRenderLayer::createNewInstance(const MeshDesc &desc) {
        InstanceID instanceId = 0;
        /*
         * Desc can be taken in via reference because the caller thread will be blocked until the mesh is created.
         * The desc object will not go out of scope.
         */
        m_RenderThread.pushTaskSync([&desc, &instanceId, this]{
            instanceId = m_GeometryPass->createNewInstance(desc);
        });
        return instanceId;
    }

    InstanceID PBRenderLayer::createNewInstanceFromOther(InstanceID otherInstance) {
        InstanceID instanceId = 0;
        m_RenderThread.pushTaskSync([&otherInstance, &instanceId, this]{
            instanceId = m_GeometryPass->createNewInstanceFromOther(otherInstance);
        });
        return instanceId;
    }

    void PBRenderLayer::setTransformation(InstanceID instanceId, const glm::mat4& modelMatrix) {
        m_RenderThread.pushTask([instanceId, modelMatrix, this]{
            m_GeometryPass->setTransformation(instanceId, modelMatrix);
        });
    }

    void PBRenderLayer::removeInstance(InstanceID instanceId) {
        m_RenderThread.pushTask([instanceId, this]{
            m_GeometryPass->removeInstance(instanceId);
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

    void PBRenderLayer::instanceSetMaterial(InstanceID instanceId, MaterialID materialID) {
        m_RenderThread.pushTaskSync([instanceId, materialID, this]{
            m_GeometryPass->instanceSetMaterial(instanceId, materialID);
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
            lid = m_LightDataPass->createLight(lightDesc);
        });
        return lid;
    }

    void PBRenderLayer::removeLight(LightID lightID) {
        m_RenderThread.pushTaskSync([lightID, this]{
            m_LightDataPass->removeLight(lightID);
        });
    }

    void PBRenderLayer::setLightPosition(LightID lightID, const glm::vec3 &position) {
        m_RenderThread.pushTask([lightID, position, this]{ // dont need to sync because the light data pass is thread safe, but dont take position by reference
            m_LightDataPass->setLightPosition(lightID, position);
        });
    }

    void PBRenderLayer::setLightColor(LightID lightID, const glm::vec3 &color) {
        m_RenderThread.pushTask([lightID, color, this]{ // same reason
            m_LightDataPass->setLightColor(lightID, color);
        });
    }

}