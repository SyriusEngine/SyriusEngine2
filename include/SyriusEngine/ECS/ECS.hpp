#pragma once

#include "Component.hpp"
#include "EcsDefs.hpp"
#include <any>

namespace Syrius{

    typedef std::vector<std::any> ComponentData;
    typedef std::unordered_map<ComponentID, Offset> Entity;

    class SR_API ECS{
    public:

        ECS() = default;

        ~ECS() = default;

        inline EntityID createEntity(){
            std::lock_guard<std::mutex> lock(m_Mutex);

            EntityID eid = generateID();
            m_Entities.insert({eid, std::unordered_map<ComponentID, Offset>()});
            return eid;
        }

        template<typename C, typename... Args>
        void addComponent(EntityID eid, Args&&... args){
            SR_PRECONDITION(m_Entities.find(eid) != m_Entities.end(), SR_MESSAGE_ECS, "Entity: %ul does not exists", eid);

            std::lock_guard<std::mutex> lock(m_Mutex);

            auto cID = Component<C>::getID();
            if (m_ComponentMap.find(cID) == m_ComponentMap.end()){
                m_ComponentMap.insert({cID, std::vector<std::any>()});
            }
            auto& data = m_ComponentMap[cID];
            data.emplace_back(std::apply([](Args&&... args){
                return C{std::forward<Args>(args)...};
            }, std::make_tuple(std::forward<Args>(args)...)));

            m_Entities[eid].insert({cID, data.size() - 1});
        }

        template<typename C>
        C& getComponent(EntityID eid){
            auto cID = Component<C>::getID();
            auto componentOffset = m_Entities[eid][cID];
            return m_ComponentMap[cID][componentOffset];
        }

        template<typename C>
        void runSystem(void(*componentFunc)(C&)){
            auto cID = Component<C>::getID();
            auto& data = m_ComponentMap[cID];
            for (auto& comp: data){
                componentFunc(comp);
            }
        }



    private:

        std::unordered_map<ComponentID, ComponentData> m_ComponentMap;
        std::unordered_map<EntityID, Entity> m_Entities;
        std::mutex m_Mutex;


    };

}