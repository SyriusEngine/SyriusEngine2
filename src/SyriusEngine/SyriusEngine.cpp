#include "../../include/SyriusEngine/SyriusEngine.hpp"
#include "SyriusEngineImpl.hpp"

namespace Syrius{

    SyriusEngine::~SyriusEngine() = default;

    SyriusEngine::SyriusEngine(const SyriusEngineDesc &desc):
    m_Window(createWindow(desc.window)){

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
