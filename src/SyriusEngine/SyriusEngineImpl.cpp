#include "SyriusEngineImpl.hpp"

namespace Syrius{

    SyriusEngineImpl::SyriusEngineImpl(const SyriusEngineDesc &desc) :
    SyriusEngine(desc),
    m_LayerStack(createUP<LayerStack>()){
        RendererDesc rendererDesc;
        rendererDesc.api = SR_API_D3D11;
        rendererDesc.shaderLibraryPath = "./Resources/Shaders/";
        m_Renderer = createUP<Renderer>(rendererDesc, m_LayerStack, m_Window);

    }

    SyriusEngineImpl::~SyriusEngineImpl() {

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
}
