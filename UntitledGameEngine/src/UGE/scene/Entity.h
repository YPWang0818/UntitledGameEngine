#pragma once
#include "ugepch.h"
#include "entt.hpp"
#include "Scene.h"


namespace UGE {

	class Entity {

	public:
		
		Entity() = default;

		Entity(const entt::entity& entityHandle, Scene* scene)
			:m_EntityHandle(entityHandle), m_Scene(scene)
		{
			
		};
	
		entt::entity getEnttHandle() const { return m_EntityHandle; };

		~Entity() = default;

	
		template<typename T>
		bool HasComponent() {
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		};
	
		template<typename T, typename... Args>
		T& AddComponent(Args&&...args) {
			UGE_CORE_ASSERT(!HasComponent<T>(), "Component already exisits.");

			return m_Scene->m_Registry.emplace<T>(m_EntityHandle ,std::forward<Args>(args)...);
		};


		template<typename T>
		void RemoveComponent() {
			UGE_CORE_ASSERT(HasComponent<T>(), "Component dosen't exisits.");
		
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		T& GetComponent() {
			UGE_CORE_ASSERT(HasComponent<T>(), "Component dosen't exisits.");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		
		}

	private:

		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;

	};




}