#include "../../include/SyriusEngine/Renderer/RenderLayer.hpp"

namespace Syrius{

    RenderLayer::~RenderLayer() {

    }

    RenderLayer::RenderLayer(ResourceView<Context> &context):
    m_Context(context){

    }
}
