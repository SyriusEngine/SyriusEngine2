#pragma once

#include "Layer.hpp"
#include "Debug.hpp"

#include "Renderer/Primitives.hpp"
#include "Renderer/RenderLayer.hpp"

#include "ECS/ECS.hpp"
#include "ECS/CameraComponent.hpp"
#include "ECS/ModelComponent.hpp"
#include "ECS/LightComponent.hpp"

namespace Syrius{

    struct SR_API SyriusEngineDesc{
        WindowDesc window;
        SR_SUPPORTED_API renderAPI = SR_API_OPENGL;
        std::string shaderLibraryPath;
    };

    class SR_API SyriusEngine{
    public:
        virtual ~SyriusEngine();

        virtual void run() = 0;

        virtual void pushLayer(RCP<Layer> layer) = 0;

        virtual void pushRenderLayer(RCP<RenderLayer> renderLayer) = 0;

        virtual void popLayer(uint32 popCount) = 0;

        virtual void close() = 0;

        [[nodiscard]] virtual const UP<RenderContext>& getRenderContext() const = 0;

        virtual void addCameraComponent(EntityID eid, float sensitivity, float speed) = 0;

        [[nodiscard]] virtual CameraComponent& getCameraComponent(EntityID eid) = 0;

        virtual void removeCameraComponent(EntityID eid) = 0;

        virtual void addModelComponent(EntityID eid) = 0;

        virtual void addModelComponent(EntityID eid, const std::string& modelPath) = 0;

        [[nodiscard]] virtual ModelComponent& getModelComponent(EntityID eid) = 0;

        virtual void removeModelComponent(EntityID eid) = 0;

        virtual MaterialID createMaterial(const MaterialDesc& desc) = 0;

        virtual void removeMaterial(MaterialID materialID) = 0;

        virtual void addLightComponent(EntityID eid, const LightDesc& lightDesc) = 0;

        virtual void removeLightComponent(EntityID eid) = 0;

        EntityID createEntity();

        ResourceView<SyriusWindow> getInternalWindow();

    protected:

        explicit SyriusEngine(const SyriusEngineDesc& desc);

    protected:
        Resource<SyriusWindow> m_Window;
        UP<ECS> m_ECS;

    };

    SR_API void init();

    SR_API void terminate();

    SR_API UP<SyriusEngine> createEngine(const SyriusEngineDesc& desc);

}