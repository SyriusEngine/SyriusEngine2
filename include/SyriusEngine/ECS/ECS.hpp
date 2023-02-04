#pragma once

#include "Component.hpp"
#include "EcsDefs.hpp"
#include <any>

namespace Syrius{

    typedef std::vector<std::any> ComponentData;
    typedef std::vector<ComponentID> Entity;

    class SR_API ECS{
    public:

        ECS() = default;

        ~ECS() = default;

        inline EntityID createEntity(){
            std::lock_guard<std::mutex> lock(m_Mutex);

            EntityID eid = generateID();
            m_Entities.insert({eid, std::vector<ComponentID>()});
            return eid;
        }

        template<typename Component, typename... Args>
        void addComponent(EntityID eid, Args&&... args){

        }



    private:

        std::unordered_map<ComponentID, ComponentData> m_ComponentMap;
        std::unordered_map<EntityID, Entity> m_Entities;

        std::mutex m_Mutex;


    };

}