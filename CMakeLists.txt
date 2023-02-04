cmake_minimum_required(VERSION 3.0)
project(SyriusEngine2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./Dependencies/SyriusCore/)

add_compile_definitions(SR_EXPORT_DLL)

include_directories(./Dependencies/SyriusCore/include)
include_directories(./Dependencies/glm)


set(RENDERER_SRC
        src/SyriusEngine/Renderer/Primitives.cpp
        src/SyriusEngine/Renderer/RenderLayer.cpp)

set(SYRIUS_ENGINE_SRC
        ${RENDERER_SRC}
        src/SyriusEngine/SyriusEngine.cpp
        src/SyriusEngine/Debug.cpp
        src/SyriusEngine/LayerStack.cpp
        src/SyriusEngine/Layer.cpp
        src/SyriusEngine/SyriusEngineImpl.cpp include/SyriusEngine/ECS/Component.hpp)

add_library(SyriusEngine SHARED ${SYRIUS_ENGINE_SRC})

add_executable(SyriusEngineDev main.cpp)

if (WIN32)
    link_directories(cmake-build-debug)
    link_directories(cmake-build-debug/Dependencies/SyriusCore)

    if (MINGW)
        message("Platform: Win32, toolchain: MinGW")
        set(SYRIUS_ENGINE_LIBS
                ${CMAKE_BINARY_DIR}\\libSyriusCore.dll
                )

    elseif(MSVC)
        message("Platform: Win32, toolchain: MSVC")

        set(SYRIUS_ENGINE_LIBS
                SyriusCore
                )
    endif()

elseif(UNIX)
    message("Platform: Unix, toolchain: unknown")
endif()

target_link_libraries(SyriusEngine ${SYRIUS_ENGINE_LIBS})
target_link_libraries(SyriusEngineDev
        ${CMAKE_BINARY_DIR}\\libSyriusCore.dll
        ${CMAKE_BINARY_DIR}\\libSyriusEngine.dll)


