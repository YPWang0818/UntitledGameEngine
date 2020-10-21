#include "ugepch.h"
#include "glm/glm.hpp"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace UGE {



	Scene::Scene(const std::string& Name)
		:m_SceneName(Name)
	{
		m_SceneEntity = m_Registry.create();
		m_Registry.emplace<SceneIDComponent>(m_SceneEntity, m_SceneUUID);
	}

	Scene::~Scene()
	{
		m_Registry.clear();
	}

	Entity Scene::CreateEntity(const std::string& Name)
	{

		Entity entity{ m_Registry.create(), this };

		auto idComponent = entity.AddComponent<IDComponent>();
		auto transformComponent = entity.AddComponent<TransformComponent>(glm::mat4(1.0f));

		if (!Name.empty()) entity.AddComponent<TagComponent>(Name);
		m_EntityMap[idComponent.id] = entity;

		return entity;
	}

	Entity Scene::GetEntityByTag(const std::string& Name)
	{
		
		auto view = m_Registry.view<TagComponent>();
		for (auto ent : view) {
			const auto& tag = view.get<TagComponent>(ent).ComponentName;
			if (tag == Name) return Entity{ ent, this };

		}

		UGE_WARN("Scene::GetEntityByTag No tag match the name :{0}", Name);
		return Entity{};
	}
	

	void Scene::RemoveEntity(const Entity& entity)
	{
		m_Registry.remove(entity.getEnttHandle());
	}

}