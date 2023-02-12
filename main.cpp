#include <iostream>
#include "include/SyriusEngine/SyriusEngine.hpp"


int main() {
    using namespace Syrius;

    init();
    try{
        SyriusEngineDesc desc;

        auto engine = createEngine(desc);

        engine->run();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;

    } catch (...) {
        std::cerr << "Unknown Error" << std::endl;
    }

    terminate();

    return 0;
}
