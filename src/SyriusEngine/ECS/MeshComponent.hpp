#pragma once

#include "../../../include/SyriusEngine/Renderer/Primitives.hpp"
#include "../../../include/SyriusEngine/ECS/ModelComponent.hpp"

namespace Syrius{

    class MeshComponent: public ModelComponent{
    public:
        MeshComponent(const MeshDesc& desc, RCP<PBRenderLayer>& renderLayer);

        ~MeshComponent() override;

        void setTransformation(const glm::mat4& transformation) override;

        void setMaterial(MaterialID materialID) override;

    private:
        MeshID m_MeshID;

    };

}