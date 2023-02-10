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
            std::lock_guard<std::mutex> lock(m_Mutex);

            auto cID = Component<C>::getID();
            auto componentOffset = m_Entities[eid][cID];
            return std::any_cast<C&>(m_ComponentMap[cID][componentOffset]);
        }

        template<typename C>
        void removeComponent(EntityID eid){
            std::lock_guard<std::mutex> lock(m_Mutex);

            auto cID = Component<C>::getID();
            auto& data = m_ComponentMap[cID];
            auto componentIndex = m_Entities[eid][cID];
            if (componentIndex != data.size() - 1) {
                // Swap the component with the last one, so we don't have to erase
                // the entire vector, which is an expensive operation
                std::swap(data[componentIndex], data.back());
            }
            data.pop_back();
            m_Entities[eid].erase(cID);
        }

        template<typename C>
        void runSystem(void(*componentFunc)(C&)){
            std::lock_guard<std::mutex> lock(m_Mutex);

            auto cID = Component<C>::getID();
            auto& data = m_ComponentMap[cID];
            for (auto& comp: data){
                componentFunc(*std::any_cast<C>(&comp));
            }
        }



    private:

        std::unordered_map<ComponentID, ComponentData> m_ComponentMap;
        std::unordered_map<EntityID, Entity> m_Entities;
        std::mutex m_Mutex;


    };

}