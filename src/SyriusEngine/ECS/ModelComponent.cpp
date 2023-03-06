#include "../../../include/SyriusEngine/ECS/ModelComponent.hpp"
#include "Builtins.hpp"

namespace Syrius{

    ModelComponent::ModelComponent(RCP<PBRenderLayer>& renderLayer):
            m_RenderLayer(renderLayer),
            m_Rotate(0.0f, 0.0f, 0.0f),
            m_Scale(1.0f, 1.0f, 1.0f),
            m_Translate(0.0f, 0.0f, 0.0f),
            m_Transformation(glm::mat4(1.0f)){

    }

    ModelComponent::~ModelComponent() = default;

    void ModelComponent::setTranslate(const glm::vec3 &translate) {
        m_Translate = translate;
        calculateTransformation();
    }

    void ModelComponent::setRotate(const glm::vec3 &rotate) {
        m_Rotate = rotate;
        calculateTransformation();
    }

    void ModelComponent::setScale(const glm::vec3 &scale) {
        m_Scale = scale;
        calculateTransformation();
    }

    const glm::vec3 &ModelComponent::getTranslate() const {
        return m_Translate;
    }

    const glm::vec3 &ModelComponent::getRotate() const {
        return m_Rotate;
    }

    const glm::vec3 &ModelComponent::getScale() const {
        return m_Scale;
    }

    RCP<ModelComponent> &ModelComponent::addSubModel() {
        m_ChildModels.emplace_back();
        return m_ChildModels.back();
    }

    RCP<ModelComponent> &ModelComponent::addSubMesh(const MeshDesc &desc) {
        m_ChildModels.emplace_back(createUP<MeshComponent>(desc, m_RenderLayer));
        return m_ChildModels.back();
    }

    RCP<ModelComponent> ModelComponent::addCube() {
        m_ChildModels.emplace_back(createUP<Cube>(m_RenderLayer));
        return m_ChildModels.back();
    }

    RCP<ModelComponent> ModelComponent::addQuad() {
        m_ChildModels.emplace_back(createUP<Quad>(m_RenderLayer));
        return m_ChildModels.back();
    }

    RCP<ModelComponent> ModelComponent::addTriangle() {
        m_ChildModels.emplace_back(createUP<Triangle>(m_RenderLayer));
        return m_ChildModels.back();
    }

    RCP<ModelComponent> ModelComponent::addPyramid() {
        m_ChildModels.emplace_back(createUP<Pyramid>(m_RenderLayer));
        return m_ChildModels.back();
    }

    RCP<ModelComponent> ModelComponent::addCone(uint32 rings) {
        m_ChildModels.emplace_back(createUP<Cone>(m_RenderLayer, rings));
        return m_ChildModels.back();
    }

    RCP<ModelComponent> ModelComponent::addSphere(uint32 rings, uint32 sectors) {
        m_ChildModels.emplace_back(createUP<Sphere>(m_RenderLayer, rings, sectors));
        return m_ChildModels.back();
    }

    RCP<ModelComponent> ModelComponent::addTorus(uint32 rings, uint32 sectors) {
        m_ChildModels.emplace_back(createUP<Torus>(m_RenderLayer, rings, sectors));
        return m_ChildModels.back();
    }

    void ModelComponent::setTransformation(const glm::mat4 &transformation) {
        m_Transformation = transformation;
    }

    void ModelComponent::propagateTransformation(const glm::mat4 &transformation) {
        m_Transformation *= transformation;
        setTransformation(m_Transformation);
        for (const auto& child: m_ChildModels){
            child->propagateTransformation(m_Transformation);
        }
    }

    void ModelComponent::calculateTransformation() {
        glm::mat4 translate = glm::translate(m_Translate);
        glm::mat4 rotate = glm::toMat4(glm::quat(m_Rotate));
        glm::mat4 scale = glm::scale(m_Scale);

        propagateTransformation(translate * rotate * scale);
    }

    void ModelComponent::setMaterial(MaterialID materialID) {
        for (const auto& child: m_ChildModels){
            child->setMaterial(materialID);
        }
    }

}
