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

    void ModelLoader::processNode(aiNode *node, RCP<ModelComponent> model) {



    }

    void ModelLoader::processMesh(aiMesh *mesh) {

    }

    void ModelLoader::processMaterial(aiMaterial *material, MaterialID &matid) {

    }
}