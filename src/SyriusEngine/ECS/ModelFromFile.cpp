#include "ModelFromFile.hpp"
#include "../Renderer/PBRenderLayer/PBRenderLayer.hpp"

namespace Syrius{

    ModelFromFile::ModelFromFile(RCP<PBRenderLayer> &renderLayer, const std::string &modelPath):
    ModelComponent(renderLayer){
        Assimp::Importer importer;
        const auto* scene = importer.ReadFile(modelPath, aiProcess_Triangulate |
                                          aiProcess_FlipUVs |
                                          aiProcess_CalcTangentSpace |
                                          aiProcess_GenNormals |
                                          aiProcess_JoinIdenticalVertices |
                                          aiProcess_OptimizeMeshes |
                                          aiProcess_OptimizeGraph);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            SR_MESSAGE_EXCEPTION(SR_MESSAGE_SOURCE::SR_MESSAGE_GENERAL, "Failed to load model from: %s, details: %s", modelPath.c_str(), importer.GetErrorString());
        }
        auto lastSlash = modelPath.find_last_of('/');
        auto lastBackSlash = modelPath.find_last_of('\\');
        if (lastSlash == std::string::npos){
            m_FilePath = modelPath.substr(0, lastBackSlash);
        }
        else{
            m_FilePath = modelPath.substr(0, lastSlash);
        }

        processNode(scene->mRootNode, scene);
    }

    ModelFromFile::~ModelFromFile() {

    }

    void ModelFromFile::processNode(aiNode *node, const aiScene* scene) {
        for (uint32 i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh, scene);
        }

        for (uint32 i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    void ModelFromFile::processMesh(aiMesh *mesh, const aiScene* scene) {
        MeshDesc meshDesc;

        for (uint32 i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            if (mesh->mTextureCoords[0]) {
                vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            } else {
                vertex.texCoord = glm::vec2(0.0f, 0.0f);
            }
            meshDesc.vertices.push_back(vertex);
        }

        for (uint32 i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (uint32 j = 0; j < face.mNumIndices; j++) {
                meshDesc.indices.push_back(face.mIndices[j]);
            }
        }

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        processMaterial(material, meshDesc.materialID);

        addSubMesh(meshDesc);

    }

    void ModelFromFile::processMaterial(aiMaterial *material, MaterialID &matid) {
        aiString path;
        std::string albedoPath;
        std::string normalPath;
        std::string metallicPath;
        std::string roughnessPath;
        std::string aoPath;
        std::string hash;
        if (material->GetTexture(aiTextureType_BASE_COLOR, 0, &path) == AI_SUCCESS) {
            std::string filename = std::string(path.C_Str());
            filename = m_FilePath + '/' + filename;
            albedoPath = filename;
            hash += filename;
        }
        else if (material->GetTexture(aiTextureType_NORMALS, 0, &path) == AI_SUCCESS) {
            std::string filename = std::string(path.C_Str());
            filename = m_FilePath + '/' + filename;
            normalPath = filename;
            hash += filename;
        }
        else if (material->GetTexture(aiTextureType_METALNESS, 0, &path) == AI_SUCCESS) {
            std::string filename = std::string(path.C_Str());
            filename = m_FilePath + '/' + filename;
            metallicPath = filename;
            hash += filename;
        }
        else if (material->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &path) == AI_SUCCESS) {
            std::string filename = std::string(path.C_Str());
            filename = m_FilePath + '/' + filename;
            roughnessPath = filename;
            hash += filename;
        }
        else if (material->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &path) == AI_SUCCESS) {
            std::string filename = std::string(path.C_Str());
            filename = m_FilePath + '/' + filename;
            aoPath = filename;
            hash += filename;
        }
        if (hash.empty()){
            matid = 0;
            return;
        }

        if (m_Materials.find(hash) == m_Materials.end()) {
            MaterialDesc matDesc;
            matDesc.albedo = createImage(albedoPath);
            matDesc.normal = createImage(normalPath);
            matDesc.metallic = createImage(metallicPath);
            matDesc.roughness = createImage(roughnessPath);
            matDesc.ao = createImage(aoPath);
            matid = m_RenderLayer->createMaterial(matDesc);
            m_Materials[hash] = matid;
        }
        else {
            matid = m_Materials[hash];
        }
    }

}