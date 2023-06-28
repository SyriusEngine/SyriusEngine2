#include <iostream>
#include "ApplicationLayer.hpp"

void runEngine(SR_SUPPORTED_API api, uint32 width, uint32 height, int32 x, int32 y){
    SyriusEngineDesc desc;
    desc.window.width = width;
    desc.window.height = height;
    desc.window.xPos = x;
    desc.window.yPos = y;
    desc.renderAPI = api;
    desc.window.title = "SyriusEngine - " + Syrius::getAPIName(api);
    auto engine = createEngine(desc);
    auto appLayer = createRCP<ApplicationLayer>(engine);
    engine->pushRenderLayer(appLayer);
    engine->run();
}

int main() {
    init();
    try{
        runEngine(Syrius::SR_API_D3D11, 1280, 720, 100, 100);


    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

    } catch (...) {
        std::cerr << "Unknown Error" << std::endl;
    }

    terminate();

    return 0;
}
