#include <iostream>
#include "include/SyriusEngine/SyriusEngine.hpp"
#include "include/SyriusEngine/ECS/ECS.hpp"

struct Color{
    float r;
    float g;
    float b;

    Color(float r, float g, float b) : r(r), g(g), b(b){}
};

int main() {
    using namespace Syrius;
    ECS ecs;

    auto e1 = ecs.createEntity();
    auto e2 = ecs.createEntity();

    ecs.addComponent<Color>(e1, 0.2, 0.3, 0.4f);


//    init();
//    try{
//        SyriusEngineDesc desc;
//
//        auto engine = createEngine(desc);
//
//        engine->run();
//
//    } catch (std::exception& e) {
//        std::cerr << e.what() << std::endl;
//
//    } catch (...) {
//        std::cerr << "Unknown Error" << std::endl;
//    }
//
//    terminate();

    return 0;
}
