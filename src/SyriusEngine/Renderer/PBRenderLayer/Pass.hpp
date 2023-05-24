#pragma once

#include "RenderGraphDefs.hpp"
#include "../RenderData.hpp"

namespace Syrius{

    class Pass {
    public:
        Pass() = delete;

        explicit Pass(ResourceView<Context>& context, NodeClass nClass, NodeType nType, PassType pType);

        virtual ~Pass();

        virtual void execute() = 0;

        [[nodiscard]] UID getPassID() const;

        [[nodiscard]] NodeClass getNodeClass() const;

        [[nodiscard]] NodeType getNodeType() const;

        [[nodiscard]] PassType getPassType() const;

        [[nodiscard]] const std::vector<PassType>& getDependencies() const;

        PassDesc getPassDesc();

    protected:

        void addDependency(PassType pType);

    protected:

        ResourceView<Context>& m_Context;

    private:
        UID m_PassID;
        const NodeClass m_NodeClass;
        const NodeType m_NodeType;
        const PassType m_PassType;

        std::vector<PassType> m_Dependencies;

    };

}