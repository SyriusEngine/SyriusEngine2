#include "CameraDataPass.hpp"

namespace Syrius{

    struct CameraData{
        glm::mat4 m_ViewMatrix      = glm::mat4(1.0f);
        glm::vec4 m_CameraPosition  = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    };

    ConstantBufferDesc createDesc(){
        ConstantBufferDesc desc;
        desc.name = "CameraData";
        desc.size = sizeof(CameraData);
        desc.slot = 1;
        CameraData cData;
        desc.data = &cData;
        desc.type = SR_BUFFER_DYNAMIC;
        desc.shaderStage = SR_SHADER_VERTEX;
        return desc;
    }

    CameraDataPass::CameraDataPass(ResourceView<Context>& context)
    : ResourcePass(context, createDesc()) {

    }

    CameraDataPass::~CameraDataPass() {

    }

    void CameraDataPass::setCameraData(const glm::mat4 &viewMat, const glm::vec3 &camPos) {
        CameraData data;
        data.m_ViewMatrix = viewMat;
        data.m_CameraPosition = glm::vec4(camPos, 1.0f);
        m_Resource->setData(&data);
    }
}