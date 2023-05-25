#pragma once

#include "Pass.hpp"

namespace Syrius{

    class SamplerPass: public Pass{
    public:
        SamplerPass(ResourceView<Context>& context, const SamplerDesc& desc, PassType pType, uint32 slot);

        ~SamplerPass() override;

        void execute() override;

    private:
        uint32 m_Slot;
        ResourceView<Sampler> m_Resource;
    };

    class LinearFilterWrapRepeatSamplerPass: public SamplerPass{
    public:
        explicit LinearFilterWrapRepeatSamplerPass(ResourceView<Context>& context);

        ~LinearFilterWrapRepeatSamplerPass() override;

    };

}