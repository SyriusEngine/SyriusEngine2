#include "ProjectionPass.hpp"

namespace Syrius{

    struct ProjectionData{
        glm::mat4 m_Perspective = glm::mat4(1.0f);
        glm::mat4 m_Orthogonal = glm::mat4(1.0f);
    };

    ConstantBufferDesc createDesc(const ProjectionDesc& pDesc){
        ConstantBufferDesc desc;
        desc.name = "ProjectionData";
        desc.size = sizeof(ProjectionData);
        desc.slot = 0;
        desc.shaderStage = SR_SHADER_VERTEX;
        desc.type = SR_BUFFER_DYNAMIC;
        ProjectionData pData;
        pData.m_Perspective = glm::perspective(pDesc.m_Fov, pDesc.m_Width / pDesc.m_Height, pDesc.m_Near, pDesc.m_Far);
        pData.m_Orthogonal = glm::ortho(pDesc.m_Xpos, pDesc.m_Width, pDesc.m_Ypos, pDesc.m_Height);
        desc.data = &pData;

        return desc;
    }

    ProjectionPass::ProjectionPass(ResourceView<Context>& context, const ProjectionDesc& pDesc)
    : ResourcePass(context, createDesc(pDesc)),
    m_ProjectionDesc(pDesc){
        setProjectionData();
    }

    ProjectionPass::~ProjectionPass() {

    }

    void ProjectionPass::onResize(uint32 width, uint32 height) {
        m_ProjectionDesc.m_Width = static_cast<float>(width);
        m_ProjectionDesc.m_Height = static_cast<float>(height);
        setProjectionData();
    }

    void ProjectionPass::setPosition(int32 xpos, int32 ypos) {
        m_ProjectionDesc.m_Xpos = static_cast<float>(xpos);
        m_ProjectionDesc.m_Ypos = static_cast<float>(ypos);
        setProjectionData();

    }

    void ProjectionPass::setFOV(float fov) {
        m_ProjectionDesc.m_Fov = fov;
        setProjectionData();
    }

    void ProjectionPass::setDepth(float near, float far) {
        m_ProjectionDesc.m_Near = near;
        m_ProjectionDesc.m_Far = far;
        setProjectionData();
    }

    void ProjectionPass::setProjectionData() {
        ProjectionData pData;
        pData.m_Perspective = glm::perspective(m_ProjectionDesc.m_Fov, m_ProjectionDesc.m_Width / m_ProjectionDesc.m_Height, m_ProjectionDesc.m_Near, m_ProjectionDesc.m_Far);
        pData.m_Orthogonal = glm::ortho(m_ProjectionDesc.m_Xpos, m_ProjectionDesc.m_Width, m_ProjectionDesc.m_Ypos, m_ProjectionDesc.m_Height);
        m_Resource->setData(&pData);
    }

}