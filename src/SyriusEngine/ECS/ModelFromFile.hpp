#pragma once

#include "MeshComponent.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Syrius{

    class ModelFromFile: public ModelComponent{
    public:
        ModelFromFile(RCP<PBRenderLayer>& renderLayer, const std::string& modelPath);

        ~ModelFromFile() override;

    private:

        void processNode(aiNode* node, const aiScene* scene);

        void processMesh(aiMesh* mesh, const aiScene* scene);

        void processMaterial(aiMaterial* material, MaterialID& matid);

    private:
        std::string m_FilePath;
        std::unordered_map<std::string, MaterialID> m_Materials;

    };

}