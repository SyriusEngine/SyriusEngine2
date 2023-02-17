#include <iostream>
#include "ApplicationLayer.hpp"


int main() {
    init();
    try{
        ////// OPENGL
//        SyriusEngineDesc glDesc;
//        glDesc.renderAPI = SR_API_OPENGL;
//        glDesc.window.title = "SyriusEngine - OpenGL";
//        auto glEngine = createEngine(glDesc);
//        auto glApp = createRCP<ApplicationLayer>(glEngine);
//        glEngine->pushLayer(glApp);
//        glEngine->run();


        ////// D3D11
        SyriusEngineDesc d3d11Desc;
        d3d11Desc.renderAPI = SR_API_D3D11;
        d3d11Desc.window.title = "SyriusEngine - D3D11";
        auto d3d11Engine = createEngine(d3d11Desc);
        auto d3d11App = createRCP<ApplicationLayer>(d3d11Engine);
        d3d11Engine->pushLayer(d3d11App);
        d3d11Engine->run();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

    } catch (...) {
        std::cerr << "Unknown Error" << std::endl;
    }

    terminate();

    return 0;
}
