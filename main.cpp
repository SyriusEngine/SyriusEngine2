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

struct Position{
public:
    Position():
    x(0), y(0), z(0){

    }

    Position(float x, float y, float z):
    x(x), y(y), z(z){
        printf("Position Constructor, x: %f, y: %f, z: %f\n", x, y, z);
    }

    Position(const Position& other):
    x(other.x), y(other.y), z(other.z){
        printf("Position Copy Constructor, x: %f, y: %f, z: %f\n", x, y, z);
    }

    Position(Position&& other) noexcept:
    x(other.x), y(other.y), z(other.z){
        printf("Position Move Constructor, x: %f, y: %f, z: %f\n", x, y, z);
    }

    ~Position(){
        printf("Position Destructor, x: %f, y: %f, z: %f\n", x, y, z);
    }

    void print(){
        printf("Position, x: %f, y: %f, z: %f\n", x, y, z);
    }


    float x, y, z;

};

int testVec(){
    Vector<Position> vec;

    vec.emplaceBack(1, 2, 3);
    vec.emplaceBack(4, 5, 6);
    vec.emplaceBack(7, 8, 9);

    auto& last = vec.back();
    last.print();




    return 0;
}


int main() {
    return testVec();
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
