#pragma once

#include "../../../../include/SyriusEngine/Renderer/Primitives.hpp"
#include "../../../../include/SyriusEngine/ECS/ModelComponent.hpp"
#include "../../../../include/SyriusEngine/ECS/EcsDefs.hpp"
#include "../../../../include/SyriusEngine/Debug.hpp"
#include "../../../../include/SyriusEngine/SyriusEngine.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Syrius{

    class ModelLoader{
    public:
        ModelLoader(SyriusEngine* engine, const std::string& path, EntityID entityID);

        ~ModelLoader() = default;

    private:

        void processNode(aiNode* node, RCP<ModelComponent> model);

        void processMesh(aiMesh* mesh);

        void processMaterial(aiMaterial* material, MaterialID& matid);

    private:
        SyriusEngine* m_Engine;
        std::string m_Path;

        EntityID m_EntityID;

        const aiScene* m_Scene;

    };
}