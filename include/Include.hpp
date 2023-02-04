#pragma once

#include <SyriusCore/SyriusCore.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm.hpp>
#include <ext.hpp>
#include <gtx/quaternion.hpp>

#include <memory>
#include <unordered_map>
#include <algorithm>
#include <functional>

#include "PlatformDetection.hpp"

namespace Syrius{

    typedef uint64 UID;

    template<typename T>
    using UP = std::unique_ptr<T>;

    // RCP = Reference Counting Pointer => because i'm a bit lazy and do not want to type std::shared_pointer every time
    template<typename T>
    using RCP = std::shared_ptr<T>;

    template<typename T, typename... Args>
    inline UP<T> createUP(Args&&... args){
        return std::make_unique<T>(args...);
    }

    template<typename T, typename... Args>
    inline RCP<T> createRCP(Args&&... args){
        return std::make_shared<T>(args...);
    }

    inline UID generateID(){
        return getRandom<uint64>(1, UINT64_MAX);;
    }
}