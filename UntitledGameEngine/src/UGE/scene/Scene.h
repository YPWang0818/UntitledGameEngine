#pragma once
#include "ugepch.h"
#include "entt.hpp"
#include "core/UUID.h"

namespace UGE {

	class Entity;

	using EntityMap = std::unordered_map<UUID, Entity>;

	class Scene {

	public:
		Scene(const std::string& Name);
		~Scene();

		Entity CreateEntity(const std::string& Name = "");
		Entity GetEntityByTag(const std::string& Name);

		void RemoveEntity(const Entity& entity);



	private:
		UUID m_SceneUUID;
		entt::entity m_SceneEntity;
		std::string m_SceneName;
		entt::registry m_Registry;
		EntityMap m_EntityMap;

		friend class Entity;
	};


	struct SceneIDComponent {

		UUID m_SceneID;

	};


}