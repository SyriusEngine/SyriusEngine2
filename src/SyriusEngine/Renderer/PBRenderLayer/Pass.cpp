#include "Pass.hpp"

namespace Syrius{

    Pass::Pass(ResourceView<Context>& context):
            m_Context(context),
            m_PassID(generateID()){

    }

    Pass::~Pass() {

    }

    void Pass::addInput(RCP<Pass> pass) {
        m_Inputs.push_back(pass);
    }

    UID Pass::getPassID() const {
        return m_PassID;
    }

    void Pass::executeInputPasses() {
        for (auto& pass : m_Inputs){
            pass->execute();
        }
    }
}