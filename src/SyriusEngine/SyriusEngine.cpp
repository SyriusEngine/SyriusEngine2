#include "../../include/SyriusEngine/SyriusEngine.hpp"
#include "SyriusEngineImpl.hpp"

namespace Syrius{

    SyriusEngine::~SyriusEngine() = default;

    SyriusEngine::SyriusEngine(const SyriusEngineDesc &desc):
    m_Window(createWindow(desc.window)),
    m_ECS(createUP<ECS>()){

    }

    EntityID SyriusEngine::createEntity() {
        return m_ECS->createEntity();
    }

    void SyriusEngine::destroyEntity(EntityID eid){
        m_ECS->removeEntity(eid);
    }

    ResourceView<SyriusWindow> SyriusEngine::getInternalWindow() {
        return m_Window.createView();
    }

    void init(){
        syriusCoreInit();
        MessageHandler::init();
    }

    void terminate(){

    }

    UP<SyriusEngine> createEngine(const SyriusEngineDesc& desc){
        return createUP<SyriusEngineImpl>(desc);
    }

}
