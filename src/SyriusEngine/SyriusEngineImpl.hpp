#pragma once

#include "../../include/SyriusEngine/SyriusEngine.hpp"
#include "LayerStack.hpp"
#include "Renderer/Renderer.hpp"
#include "ECS/ModelFromFile.hpp"

namespace Syrius{

    class SyriusEngineImpl: public SyriusEngine{
    public:
        explicit SyriusEngineImpl(const SyriusEngineDesc& desc);

        ~SyriusEngineImpl() override;

        void run() override;

        void pushLayer(RCP<Layer> layer) override;

        void pushRenderLayer(RCP<RenderLayer> renderLayer) override;

        void popLayer(uint32 popCount) override;

        void close() override;

        [[nodiscard]] const UP<RenderContext>& getRenderContext() const override;

        void addCameraComponent(EntityID, float sensitivity, float speed) override;

        [[nodiscard]] CameraComponent& getCameraComponent(EntityID eid) override;

        void removeCameraComponent(EntityID eid) override;

        void addModelComponent(EntityID eid) override;

        void addModelComponent(EntityID eid, const std::string& modelPath) override;

        [[nodiscard]] ModelComponent& getModelComponent(EntityID eid) override;

        void removeModelComponent(EntityID eid) override;

        MaterialID createMaterial(const MaterialDesc& desc) override;

        void removeMaterial(MaterialID materialID) override;

        void addLightComponent(EntityID eid, const LightDesc& lightDesc) override;

        void removeLightComponent(EntityID eid) override;

    private:
        UP<LayerStack> m_LayerStack;
        UP<Renderer> m_Renderer;

    };

}