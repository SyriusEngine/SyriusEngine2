#include "ModelLoader.hpp"

namespace Syrius{

    void nullDeleter(ModelComponent* ptr){}

    ModelLoader::ModelLoader(SyriusEngine* engine, const std::string &path, EntityID entityID):
    m_EntityID(entityID),
    m_Engine(engine){
        Assimp::Importer importer;
        m_Scene = importer.ReadFile(path, aiProcess_Triangulate |
                                          aiProcess_FlipUVs |
                                          aiProcess_CalcTangentSpace |
                                          aiProcess_GenNormals |
                                          aiProcess_JoinIdenticalVertices |
                                          aiProcess_OptimizeMeshes |
                                          aiProcess_OptimizeGraph);
        if (!m_Scene || m_Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !m_Scene->mRootNode) {
            SR_MESSAGE_WARNING(SR_MESSAGE_SOURCE::SR_MESSAGE_ECS, "Failed to load model from file: %s", path.c_str());
        }
        auto lastSlash = path.find_last_of('/');
        auto lastBackSlash = path.find_last_of('\\');
        if (lastSlash == std::string::npos){
            m_Path = path.substr(0, lastBackSlash);
        }
        else{
            m_Path = path.substr(0, lastSlash);
        }

        m_Engine->addModelComponent(m_EntityID);
        auto& model = m_Engine->getModelComponent(m_EntityID);
        auto modelPtr = RCP<ModelComponent>(&model, &nullDeleter); // do not call destructor for this pointer
        processNode(m_Scene->mRootNode, modelPtr);
    }

    void ModelLoader::processNode(aiNode *node, const RCP<ModelComponent>& model) {
        for (uint32 i = 0; i < node->mNumMeshes; i++){
            MeshDesc desc;
            aiMesh* mesh = m_Scene->mMeshes[node->mMeshes[i]];
            processMesh(mesh, desc);
            model->addSubMesh(desc);
        }

        for (uint32 i = 0; i < node->mNumChildren; i++){
            auto subModel = model->addSubModel();
            processNode(node->mChildren[i], subModel);
        }
    }

    void ModelLoader::processMesh(aiMesh *mesh, MeshDesc& desc) {
        desc.vertices.reserve(mesh->mNumVertices);
        desc.indices.reserve(mesh->mNumFaces * 3);

        for (uint32 i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            vertex.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
            if (mesh->HasNormals()){
                vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
            }
            if (mesh->HasTangentsAndBitangents()){
                vertex.tangent = glm::vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
            }
            if (mesh->HasTextureCoords(0)){
                vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
            }
            else{
                vertex.texCoord = glm::vec2(0.0f, 0.0f);
            }
            desc.vertices.push_back(vertex);
        }

        for (uint32 i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (uint32 j = 0; j < face.mNumIndices; j++) {
                desc.indices.push_back(face.mIndices[j]);
            }
        }

        desc.materialID = processMaterial(m_Scene->mMaterials[mesh->mMaterialIndex]);
    }

    MaterialID ModelLoader::processMaterial(aiMaterial *material) {
        if (m_Materials.find(material) != m_Materials.end()){
            return m_Materials[material];
        }
        else{
            auto loadTexture = [&](aiTextureType type){
                aiString path;
                if (material->GetTexture(type, 0, &path) == AI_SUCCESS){
                    return m_Path + "/" + path.C_Str();
                }
                else{
                    return std::string();
                }
            };
            MaterialDesc desc(
                    loadTexture(aiTextureType_BASE_COLOR),
                    loadTexture(aiTextureType_NORMALS),
                    loadTexture(aiTextureType_METALNESS),
                    loadTexture(aiTextureType_DIFFUSE_ROUGHNESS),
                    loadTexture(aiTextureType_AMBIENT_OCCLUSION)
                    );
            auto newMaterialID = m_Engine->createMaterial(desc);
            m_Materials[material] = newMaterialID;
            return newMaterialID;
        }
    }

}