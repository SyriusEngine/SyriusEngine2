#include "SyriusEngineImpl.hpp"

namespace Syrius{

    SyriusEngineImpl::SyriusEngineImpl(const SyriusEngineDesc &desc) :
    SyriusEngine(desc),
    m_LayerStack(createUP<LayerStack>()){
        RendererDesc rendererDesc;
        rendererDesc.api = desc.renderAPI;
        rendererDesc.shaderLibraryPath = "./Resources/Shaders/";
        m_Renderer = createUP<Renderer>(rendererDesc, m_LayerStack, m_Window);

    }

    SyriusEngineImpl::~SyriusEngineImpl() {
        /*
         * Kind of defeats the purpose of smart pointers, but the ECS has objects that depend on the renderer
         */
        m_ECS.reset();
        m_Renderer.reset();
    }

    void SyriusEngineImpl::run() {
        while (m_Window->isOpen()){

            m_Window->pollEvents();
            while (m_Window->hasEvent()){
                auto event = m_Window->getEvent();
                if (event.type == SR_EVENT_WINDOW_CLOSED){
                    m_Window->close();
                }
                else{
                    m_LayerStack->onEvent(event);
                }
            }

            m_LayerStack->onUpdate();

            m_Renderer->render();
        }

    }

    void SyriusEngineImpl::pushLayer(RCP<Layer> layer) {
        m_LayerStack->pushLayer(layer);
    }

    void SyriusEngineImpl::pushRenderLayer(RCP<RenderLayer> renderLayer) {
        m_LayerStack->pushRenderLayer(renderLayer);
    }

    void SyriusEngineImpl::close() {
        m_Window->close();
    }

    void SyriusEngineImpl::popLayer(uint32 popCount) {
        m_LayerStack->popLayer(popCount);
    }

    const UP<RenderContext> &SyriusEngineImpl::getRenderContext() const {
        return m_Renderer->getRenderContext();
    }

    void SyriusEngineImpl::addCameraComponent(EntityID eid, float sensitivity, float speed) {
        auto& renderLayer = m_Renderer->getPBRenderLayer();
        m_ECS->addComponent<CameraComponent>(eid, sensitivity, speed, renderLayer);
    }

    CameraComponent &SyriusEngineImpl::getCameraComponent(EntityID eid) {
        return m_ECS->getComponent<CameraComponent>(eid);
    }

    void SyriusEngineImpl::removeCameraComponent(EntityID eid) {
        m_ECS->removeComponent<CameraComponent>(eid);
    }

    void SyriusEngineImpl::addModelComponent(EntityID eid) {
        m_ECS->addComponent<ModelComponent>(eid, m_Renderer->getPBRenderLayer());
    }

    void SyriusEngineImpl::addModelComponent(EntityID eid, const std::string &modelPath) {
        ModelLoader loader(this, modelPath, eid);
    }

    ModelComponent &SyriusEngineImpl::getModelComponent(EntityID eid) {
        return m_ECS->getComponent<ModelComponent>(eid);
    }

    void SyriusEngineImpl::removeModelComponent(EntityID eid) {
        m_ECS->getComponent<ModelComponent>(eid).destroy(); // TODO: This is a hack, fix it
        m_ECS->removeComponent<ModelComponent>(eid);
    }

    MaterialID SyriusEngineImpl::createMaterial(const MaterialDesc &desc) {
        return m_Renderer->getPBRenderLayer()->createMaterial(desc);
    }

    void SyriusEngineImpl::removeMaterial(MaterialID materialID) {
        m_Renderer->getPBRenderLayer()->removeMaterial(materialID);
    }

    void SyriusEngineImpl::addLightComponent(EntityID eid, const LightDesc &lightDesc) {
        m_ECS->addComponent<LightComponent>(eid, lightDesc, m_Renderer->getPBRenderLayer());
    }

    LightComponent &SyriusEngineImpl::getLightComponent(EntityID eid) {
        return m_ECS->getComponent<LightComponent>(eid);
    }

    void SyriusEngineImpl::removeLightComponent(EntityID eid) {
        m_ECS->getComponent<LightComponent>(eid).destroy(); // TODO: This is a hack, fix it
        m_ECS->removeComponent<LightComponent>(eid);
    }

}
