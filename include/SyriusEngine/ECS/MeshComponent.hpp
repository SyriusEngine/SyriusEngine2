#pragma once

#include "../Renderer/Primitives.hpp"
#include "ModelComponent.hpp"

namespace Syrius{

    class MeshComponent: public ModelComponent{
    public:
        MeshComponent(const MeshDesc& desc, RCP<PBRenderLayer>& renderLayer);

        MeshComponent(InstanceID otherInstance, RCP<PBRenderLayer>& renderLayer);

        ~MeshComponent() override;

        void setTransformation(const glm::mat4& transformation) override;

        void setMaterial(MaterialID materialID) override;

        InstanceID getInstanceID() const override;

    private:
        InstanceID m_InstanceID;

    };

}