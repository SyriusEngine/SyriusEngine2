#pragma once

#include "EcsDefs.hpp"
#include <typeindex>
#include <mutex>

namespace Syrius{

    template<typename ComponentType>
    class SR_API Component{
    public:
        virtual ~Component() = default;

        static ComponentID getID(){
            std::lock_guard<std::mutex> lock(m_genIDMutex);

            auto it = m_IDMap.find(typeid(ComponentType));
            if (it != m_IDMap.end()){
                return it->second;
            }
            else{
                auto id = generateID();
                m_IDMap[typeid(ComponentType)] = id;
                return id;
            }
        }

    private:
        static std::mutex m_genIDMutex;
        static std::unordered_map<std::type_index, ComponentID> m_IDMap;


    };

}