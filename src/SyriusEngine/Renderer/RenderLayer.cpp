#include "../../include/SyriusEngine/Renderer/RenderLayer.hpp"

namespace Syrius{

    RenderLayer::~RenderLayer() {

    }

    RenderLayer::RenderLayer(const UP<RenderContext>& renderContext):
    m_RenderThread(renderContext->m_RenderThread),
    m_Context(renderContext->m_Context),
    m_DefaultSampler(renderContext->m_DefaultSampler),
    m_ShaderLibrary(renderContext->m_ShaderLibrary){

    }

}
