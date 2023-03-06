#include "LayerStack.hpp"

namespace Syrius{

    LayerStack::LayerStack() {

    }

    LayerStack::~LayerStack() {

    }

    void LayerStack::pushLayer(RCP<Layer> layer) {
        layer->onAttach();
        m_Layers.push_back(layer);

    }

    void LayerStack::pushRenderLayer(RCP<RenderLayer> renderLayer) {
        renderLayer->onAttach();
        m_RenderLayers.push_back(renderLayer);
        m_Layers.push_back(renderLayer);
    }

    void LayerStack::popLayer(uint32 popCount) {
        for (uint32 i = 0; i < popCount; i++){
            m_Layers.back()->onDetach();
            // the layers are always pushed in the same order on the layer stack, so it is sufficient to only compare
            // latest layers.
            if (m_Layers.back() == m_RenderLayers.back()){
                m_RenderLayers.pop_back();
            }
            m_Layers.pop_back();
        }
    }

    void LayerStack::onUpdate() {
        for (auto& layer : m_Layers) {
            layer->onUpdate();
        }
    }

    void LayerStack::onEvent(const Event &event) {
        if (m_Layers.empty()) {
            return;
        }
        if (m_Layers.size() == 1) {
            m_Layers.back()->onEvent(event);
            return;
        }
        for (auto i = m_Layers.rbegin(); i != m_Layers.rend(); i++) {
            if ((*i)->onEvent(event)) {
                break;
            }
        }
    }

    ResourceView<FrameBuffer> &LayerStack::onRender(ResourceView<FrameBuffer> &framebuffer) {
        for (const auto& renderLayer: m_RenderLayers){
            framebuffer = renderLayer->onRender(framebuffer);
        }
        return framebuffer;
    }
}
