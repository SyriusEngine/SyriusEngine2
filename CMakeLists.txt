cmake_minimum_required(VERSION 3.0)
project(SyriusEngine2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./Dependencies/SyriusCore/)

add_compile_definitions(SR_EXPORT_DLL)

include_directories(./Dependencies/SyriusCore/include)
include_directories(./Dependencies/glm)

set(SYRIUS_ENGINE_SRC
        src/SyriusEngine.cpp src/Debug.cpp)

add_library(SyriusEngine SHARED ${SYRIUS_ENGINE_SRC})
