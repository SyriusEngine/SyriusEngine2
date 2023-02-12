#include "../../../include/SyriusEngine/Renderer/RenderContext.hpp"

namespace Syrius{

    RenderContext::RenderContext(ResourceView<Context> &context, Worker &renderThread, ResourceView<Sampler>& defaultSampler, const std::string& shaderLibraryPath):
            m_Context(context),
            m_RenderThread(renderThread),
            m_DefaultSampler(defaultSampler),
            m_ShaderLibrary(createUP<ShaderLibrary>(context, shaderLibraryPath)){

    }

    RenderContext::~RenderContext() {

    }
}
