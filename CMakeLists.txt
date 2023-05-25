cmake_minimum_required(VERSION 3.0)
project(SyriusEngine2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(./Dependencies/SyriusCore/)

add_compile_definitions(SR_EXPORT_DLL)

include_directories(./Dependencies/SyriusCore/include)
include_directories(./Dependencies/glm)
include_directories(./Dependencies/assimp/include)

set(ECS_SRC
        src/SyriusEngine/ECS/CameraComponent.cpp
        src/SyriusEngine/ECS/ModelComponent.cpp
        src/SyriusEngine/ECS/Mesh/MeshComponent.cpp
        src/SyriusEngine/ECS/LightComponent.cpp
        src/SyriusEngine/ECS/Mesh/Builtins.cpp
        src/SyriusEngine/ECS/Mesh/ModelLoader.cpp)

set(RENDERER_SRC
        src/SyriusEngine/Renderer/Primitives.cpp
        src/SyriusEngine/Renderer/RenderLayer.cpp
        src/SyriusEngine/Renderer/Renderer.cpp
        src/SyriusEngine/Renderer/RenderContext.cpp
        src/SyriusEngine/Renderer/ShaderLibrary.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/PBRenderLayer.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/Pass.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/RenderPass.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/ResourcePass.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/CameraDataPass.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/ProjectionDataPass.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/GeometryPass.cpp
        src/SyriusEngine/Renderer/PBRenderLayer/LightPass.cpp
        src/SyriusEngine/Renderer/RenderData.cpp
        src/SyriusEngine/Renderer/RenderData.hpp
        src/SyriusEngine/Renderer/PBRenderLayer/RenderGraph.cpp src/SyriusEngine/Renderer/PBRenderLayer/LightDataPass.cpp src/SyriusEngine/Renderer/PBRenderLayer/LightDataPass.hpp)

set(UTILS_SRC
        src/SyriusEngine/Utils/Worker.cpp)

set(SYRIUS_ENGINE_SRC
        ${RENDERER_SRC}
        ${UTILS_SRC}
        ${ECS_SRC}
        src/SyriusEngine/SyriusEngine.cpp
        src/SyriusEngine/Debug.cpp
        src/SyriusEngine/LayerStack.cpp
        src/SyriusEngine/Layer.cpp
        src/SyriusEngine/SyriusEngineImpl.cpp )

add_library(SyriusEngine SHARED ${SYRIUS_ENGINE_SRC})

add_executable(SyriusEngineDev main.cpp ApplicationLayer.cpp ApplicationLayer.hpp)

if (WIN32)
    link_directories(./Dependencies/assimp/bin)
    link_directories(cmake-build-debug)
    link_directories(cmake-build-debug/Dependencies/SyriusCore)

    file(GLOB ASSIMP_DLL "./Dependencies/assimp/bin/*.dll")
    file(COPY ${ASSIMP_DLL} DESTINATION ${CMAKE_BINARY_DIR})

    if (MINGW)
        message("Platform: Win32, toolchain: MinGW")
        set(SYRIUS_ENGINE_LIBS
                ${CMAKE_BINARY_DIR}\\libSyriusCore.dll
                ${CMAKE_BINARY_DIR}\\libassimp-5.dll
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


