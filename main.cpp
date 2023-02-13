#include <iostream>
#include "include/SyriusEngine/SyriusEngine.hpp"


int main() {
    using namespace Syrius;

    init();
    try{
        ////// OPENGL
        SyriusEngineDesc glDesc;
        glDesc.renderAPI = SR_API_OPENGL;
        glDesc.window.title = "SyriusEngine - OpenGL";
        auto glEngine = createEngine(glDesc);
        glEngine->run();


        ////// D3D11
        SyriusEngineDesc d3d11Desc;
        d3d11Desc.renderAPI = SR_API_D3D11;
        d3d11Desc.window.title = "SyriusEngine - D3D11";
        auto d3d11Engine = createEngine(d3d11Desc);
        d3d11Engine->run();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

    } catch (...) {
        std::cerr << "Unknown Error" << std::endl;
    }

    terminate();

    return 0;
}
