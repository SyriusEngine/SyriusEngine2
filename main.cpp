#include <iostream>
#include "include/SyriusEngine/SyriusEngine.hpp"
#include "include/SyriusEngine/ECS/ECS.hpp"

struct Color{
    float r;
    float g;
    float b;

    Color(float r, float g, float b) : r(r), g(g), b(b){}
};

struct Position{
    int x;
    int y;

    Position(int x, int y): x(x), y(y) {}
};

void printColor(Color& c){
    std::cout << "Color: r = " << c.r << ", g = " << c.g << ", b" << c.b << std::endl;
}

int main() {
    using namespace Syrius;
    ECS ecs;

    auto e1 = ecs.createEntity();
    auto e2 = ecs.createEntity();

    ecs.addComponent<Color>(e1, 0.2f, 0.3f, 0.4f);
    ecs.addComponent<Color>(e2, 0.8f, 0.4f, 0.6f);

    ecs.addComponent<Position>(e1, 2, 3);
    ecs.addComponent<Position>(e2, 86, 4);

    ecs.runSystem<Color>(printColor);

    auto e1Color = ecs.getComponent<Color>(e1);
    auto e1Pos = ecs.getComponent<Position>(e1);

    ecs.removeComponent<Color>(e1);


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
