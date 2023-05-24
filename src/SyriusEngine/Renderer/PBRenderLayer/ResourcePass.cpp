#include "ResourcePass.hpp"

namespace Syrius{

    ResourcePass::ResourcePass(ResourceView<Context>& context, const ConstantBufferDesc &desc, PassType pType):
    Pass(context, NODE_CLASS_RESOURCE_PASS, NODE_CONSTANT_BUFFER, pType){
        m_Resource = m_Context->createConstantBuffer(desc);
    }


    ResourcePass::~ResourcePass() {

    }

    void ResourcePass::execute() {
        m_Resource->bind();
    }

}
