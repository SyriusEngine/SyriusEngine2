#include "RenderGraph.hpp"

namespace Syrius{

    RenderGraph::RenderGraph() {

    }

    RenderGraph::~RenderGraph() {

    }

    void RenderGraph::addPass(const PassDesc &desc) {
        m_Passes.insert({desc.passType, desc});
    }

    void RenderGraph::validate() {

    }

    void RenderGraph::compile() {

    }

    void RenderGraph::execute() {
        for (const auto& p : m_PassInstances){
            p->execute();
        }
    }



}
