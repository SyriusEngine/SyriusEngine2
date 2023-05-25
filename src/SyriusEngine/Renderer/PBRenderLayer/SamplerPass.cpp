#include "SamplerPass.hpp"

namespace Syrius{

    SamplerPass::SamplerPass(ResourceView<Context> &context, const SamplerDesc &desc, PassType pType, uint32 slot):
    Pass(context, NODE_CLASS_RESOURCE_PASS, NODE_SAMPLER, pType),
    m_Resource(context->createSampler(desc)),
    m_Slot(slot){

    }

    SamplerPass::~SamplerPass() {

    }

    void SamplerPass::execute() {
        m_Resource->bind(m_Slot);
    }

    LinearFilterWrapRepeatSamplerPass::LinearFilterWrapRepeatSamplerPass(ResourceView<Context> &context):
    SamplerPass(context, SamplerDesc(), LINEAR_FILTER_WRAP_REPEAT_SAMPLER_PASS, 0){

    }

    LinearFilterWrapRepeatSamplerPass::~LinearFilterWrapRepeatSamplerPass() {

    }
}