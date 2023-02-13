#include "RenderPass.hpp"

namespace Syrius{

    RenderPass::RenderPass(ResourceView<Context>& context, const ResourceView<FrameBufferDescription> &fbDesc)
    : Pass(context),
    m_VertexDescription(context->createVertexDescription()){
        m_FrameBuffer = m_Context->createFrameBuffer(fbDesc);

    }

    RenderPass::~RenderPass() {

    }

    void RenderPass::onResize(uint32 width, uint32 height) {
        m_FrameBuffer->onResize(width, height);
    }

    ResourceView<FrameBuffer>& RenderPass::getFrameBuffer() {
        return m_FrameBuffer;
    }


}