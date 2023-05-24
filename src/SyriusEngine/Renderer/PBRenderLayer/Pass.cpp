#include "Pass.hpp"

namespace Syrius{

    Pass::Pass(ResourceView<Context>& context, NodeClass nClass, NodeType nType, PassType pType):
    m_Context(context),
    m_PassID(generateID()),
    m_NodeClass(nClass),
    m_NodeType(nType),
    m_PassType(pType){

    }

    Pass::~Pass() {

    }


    UID Pass::getPassID() const {
        return m_PassID;
    }

    NodeClass Pass::getNodeClass() const {
        return m_NodeClass;
    }

    NodeType Pass::getNodeType() const {
        return m_NodeType;
    }

    PassType Pass::getPassType() const {
        return m_PassType;
    }

    const std::vector<PassType>& Pass::getDependencies() const {
        return m_Dependencies;
    }

    void Pass::addDependency(PassType pType) {
        m_Dependencies.push_back(pType);
    }

    PassDesc Pass::getPassDesc() {
        PassDesc desc;
        desc.pAddress = this;
        desc.passID = m_PassID;
        desc.nodeClass = m_NodeClass;
        desc.nodeType = m_NodeType;
        desc.passType = m_PassType;
        desc.dependencies = m_Dependencies;
        return desc;
    }
}