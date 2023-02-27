#include "RenderData.hpp"

namespace Syrius{

    RenderData::RenderData(ResourceView<Context> &context, ResourceView<Sampler> &defaultSampler, UP<ShaderLibrary> &shaderLibrary):
    context(context),
    defaultSampler(defaultSampler),
    shaderLibrary(shaderLibrary){

    }
}
