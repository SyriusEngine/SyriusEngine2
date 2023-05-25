#pragma once

#include "Pass.hpp"
#include "RenderGraphDefs.hpp"

namespace Syrius{

    typedef std::vector<PassType> Dependencies;
    typedef std::unordered_map<PassType, Dependencies> AdjacencyList;

    class RenderGraph{
    public:
        RenderGraph();

        ~RenderGraph();

        void addPass(const PassDesc& desc);

        void validate(); // checks if every pass its dependencies are also inside the graph

        void compile(); // topologically sorts the passes so that the dependencies are executed first

        void execute();

    private:

        void dfs(PassType passType, std::unordered_map<PassType, bool>& visited);



    private:
        std::unordered_map<PassType, PassDesc> m_Passes;
        std::vector<Pass*> m_PassInstances;
    };

}
