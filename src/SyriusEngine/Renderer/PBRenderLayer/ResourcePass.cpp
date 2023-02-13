#include "ResourcePass.hpp"

namespace Syrius{

    ResourcePass::ResourcePass(ResourceView<Context>& context, const ConstantBufferDesc &desc):
    Pass(context){
        m_Resource = m_Context->createConstantBuffer(desc);
    }


    ResourcePass::~ResourcePass() {
    }

    void ResourcePass::execute() {
        executeInputPasses();
        m_Resource->bind();
    }

}
