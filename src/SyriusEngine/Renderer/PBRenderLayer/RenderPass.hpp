#pragma once

#include "Pass.hpp"
#include "../ShaderLibrary.hpp"

namespace Syrius{

    class RenderPass : public Pass{
    public:

        explicit RenderPass(ResourceView<Context>& context);

        RenderPass(ResourceView<Context>& context, const ResourceView<FrameBufferDescription>& fbDesc);

        ~RenderPass() override;

        void bindColorAttachmentAsShaderResource(uint32 attachIndex, uint32 slot);

        void onResize(uint32 width, uint32 height);

        ResourceView<FrameBuffer>& getFrameBuffer();

    protected:
        ResourceView<VertexDescription> m_VertexDescription;
        ResourceView<FrameBuffer> m_FrameBuffer;
        ResourceView<Shader> m_Shader;

    };

}

