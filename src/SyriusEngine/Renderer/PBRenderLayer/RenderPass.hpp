#pragma once

#include "../RenderGraph/Pass.hpp"
#include "../../../../include/SyriusEngine/Renderer/ShaderLibrary.hpp"

namespace Syrius{

    class RenderPass : public Pass{
    public:

        RenderPass(ResourceView<Context>& context, const ResourceView<FrameBufferDescription>& fbDesc);

        ~RenderPass() override;

        void onResize(uint32 width, uint32 height);

        ResourceView<FrameBuffer>& getFrameBuffer();

    protected:
        ResourceView<VertexDescription> m_VertexDescription;
        ResourceView<FrameBuffer> m_FrameBuffer;
        ResourceView<Shader> m_Shader;

    };

}

