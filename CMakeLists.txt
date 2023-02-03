cmake_minimum_required(VERSION 3.0)
project(SyriusEngine2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./Dependencies/SyriusCore/)

install(TARGETS SyriusCore DESTINATION ${PROJECT_BINARY_DIR})
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

add_compile_definitions(SR_EXPORT_DLL)

include_directories(./Dependencies/SyriusCore/include)
include_directories(./Dependencies/glm)

add_library(SyriusEngine SHARED src/SyriusEngine.cpp)
