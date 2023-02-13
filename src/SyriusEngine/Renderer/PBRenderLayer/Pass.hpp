#pragma once

#include "../../../../include/SyriusEngine/Renderer/Primitives.hpp"

namespace Syrius{

    class Pass {
    public:
        Pass() = delete;

        explicit Pass(ResourceView<Context>& context);

        virtual ~Pass();

        virtual void execute() = 0;

        void addInput(RCP<Pass> pass);

        [[nodiscard]] UID getPassID() const;

    protected:

        void executeInputPasses();

    protected:

        ResourceView<Context>& m_Context;

    private:
        std::vector<RCP<Pass>> m_Inputs;
        UID m_PassID;

    };

}