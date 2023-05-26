#include "RenderData.hpp"

namespace Syrius{

    RenderData::RenderData(ResourceView<Context> &context, UP<ShaderLibrary> &shaderLibrary):
    context(context),
    shaderLibrary(shaderLibrary){

    }
}
