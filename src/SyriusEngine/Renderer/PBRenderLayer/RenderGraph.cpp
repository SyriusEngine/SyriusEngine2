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
        for (const auto& passDesc : m_Passes) {
            for (const auto &dependency: passDesc.second.dependencies) {
                if (m_Passes.find(dependency) == m_Passes.end()) {
                    SR_MESSAGE_EXCEPTION(SR_MESSAGE_RENDERER, "Pass %i has a dependency that is not inside the graph: ", passDesc.second.passType, dependency);
                }
            }
        }
    }

    void RenderGraph::compile() {
        std::unordered_map<PassType, bool> visited;
        for (const auto& passDesc : m_Passes){
            visited.insert({passDesc.first, false});
        }

        for (const auto& passDesc : m_Passes){
            if (!visited[passDesc.first]){
                dfs(passDesc.first, visited);
            }
        }
        return;
    }

    void RenderGraph::execute() {
        for (const auto& p : m_PassInstances){
            p->execute();
        }
    }

    void RenderGraph::dfs(PassType passType, std::unordered_map<PassType, bool> &visited) {
        visited[passType] = true;

        for (const auto& dependency : m_Passes[passType].dependencies){
            if (!visited[dependency]){
                dfs(dependency, visited);
            }
        }

        m_PassInstances.push_back(m_Passes[passType].pAddress);
    }


}
