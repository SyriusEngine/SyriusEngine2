#include "LightDataPass.hpp"

namespace Syrius{

    ConstantBufferDesc createLightDataDesc(){
        LightData lightData;

        ConstantBufferDesc desc;
        desc.name = "LightData";
        desc.size = sizeof(LightData);
        desc.slot = 3;
        desc.shaderStage = SR_SHADER_FRAGMENT;
        desc.type = SR_BUFFER_DYNAMIC;
        desc.data = &lightData;

        return desc;
    }

    LightDataPass::LightDataPass(ResourceView<Context>& context):
    ResourcePass(context, createLightDataDesc(), LIGHT_DATA_PASS),
    m_LightCount(0){

    }

    LightDataPass::~LightDataPass() {

    }

    LightID LightDataPass::createLight(const LightDesc &desc) {
        LightID lid = generateID();

        m_LightData.m_Position[m_LightCount] = glm::vec4(desc.position, 1.0f);
        m_LightData.m_Color[m_LightCount] = glm::vec4(desc.color, 1.0f);
        m_LightData.m_LightCount[0]++;
        m_KeyLightMap.insert({lid, m_LightCount});
        m_LightCount++;

        m_Resource->setData(&m_LightData);

        return lid;
    }

    void LightDataPass::removeLight(LightID index) {
        SR_PRECONDITION(m_KeyLightMap.find(index) != m_KeyLightMap.end(), SR_MESSAGE_RENDERER, "LightID: %d does not exist", index);

        auto lastIndex = m_LightCount - 1;
        for (const auto& pair: m_KeyLightMap){
            if (lastIndex == pair.second){
                //switch current light with last light
                m_LightData.m_Position[m_KeyLightMap[index]] = m_LightData.m_Position[lastIndex];
                m_LightData.m_Color[m_KeyLightMap[index]] = m_LightData.m_Color[lastIndex];
                //clear last light
                m_LightData.m_Position[lastIndex] = glm::vec4(0.0f);
                m_LightData.m_Color[lastIndex] = glm::vec4(0.0f);
            }
        }

        m_LightData.m_LightCount[0]--;
        m_Resource->setData(&m_LightData);

    }

    void LightDataPass::setLightPosition(LightID index, const glm::vec3 &position) {
        SR_PRECONDITION(m_KeyLightMap.find(index) != m_KeyLightMap.end(), SR_MESSAGE_RENDERER, "LightID: %d does not exist", index);

        m_LightData.m_Position[m_KeyLightMap[index]] = glm::vec4(position, 1.0f);
        m_Resource->setData(&m_LightData);
    }

    void LightDataPass::setLightColor(LightID index, const glm::vec3 &color) {
        SR_PRECONDITION(m_KeyLightMap.find(index) != m_KeyLightMap.end(), SR_MESSAGE_RENDERER, "LightID: %d does not exist", index);

        m_LightData.m_Color[m_KeyLightMap[index]] = glm::vec4(color, 1.0f);
        m_Resource->setData(&m_LightData);
    }
}
