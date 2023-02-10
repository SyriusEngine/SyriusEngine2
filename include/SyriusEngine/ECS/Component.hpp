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
        static std::unordered_map<std::type_index, ComponentID> m_IDMap;

    };

    template<typename ComponentType>
    std::unordered_map<std::type_index, ComponentID> Component<ComponentType>::m_IDMap;

}