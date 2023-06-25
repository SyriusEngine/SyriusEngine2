#pragma once

#include "../Renderer/Primitives.hpp"

namespace Syrius{

    class SR_API ModelComponent{
    public:
        explicit ModelComponent(RCP<PBRenderLayer>& renderLayer);

        virtual ~ModelComponent();

        void setTranslate(const glm::vec3& translate);

        void setRotate(const glm::vec3& rotate);

        void setScale(const glm::vec3& scale);

        [[nodiscard]] const glm::vec3& getTranslate() const;

        [[nodiscard]] const glm::vec3& getRotate() const;

        [[nodiscard]] const glm::vec3& getScale() const;

        RCP<ModelComponent>& addSubModel();

        RCP<ModelComponent>& addSubMesh(const MeshDesc& desc);

        RCP<ModelComponent>& addSubMesh(InstanceID otherInstance);

        RCP<ModelComponent>& addCube();

        RCP<ModelComponent>& addQuad();

        RCP<ModelComponent>& addTriangle();

        RCP<ModelComponent>& addPyramid();

        RCP<ModelComponent>& addCone(uint32 rings);

        RCP<ModelComponent>& addSphere(uint32 rings, uint32 sectors);

        RCP<ModelComponent>& addTorus(uint32 rings, uint32 sectors);

        virtual void setTransformation(const glm::mat4& transformation);

        virtual void setMaterial(MaterialID materialID);

        virtual InstanceID getInstanceID() const;

    protected:

        RCP<PBRenderLayer>& m_RenderLayer;

    private:

         void calculateTransformation();

         void propagateTransformation(const glm::mat4& transformation);

    private:

        glm::vec3 m_Translate;
        glm::vec3 m_Rotate;
        glm::vec3 m_Scale;

        glm::mat4 m_Transformation;

        std::vector<RCP<ModelComponent>> m_ChildModels;
    };

}