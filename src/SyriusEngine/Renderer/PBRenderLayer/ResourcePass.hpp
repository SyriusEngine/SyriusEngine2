#pragma once

#include "Pass.hpp"

namespace Syrius{

    class ResourcePass : public Pass{
    public:
        ResourcePass() = delete;

        ResourcePass(ResourceView<Context>& context, const ConstantBufferDesc& desc);

        ~ResourcePass() override;

        void execute() override;

    protected:
        ResourceView<ConstantBuffer> m_Resource;

    };

}

