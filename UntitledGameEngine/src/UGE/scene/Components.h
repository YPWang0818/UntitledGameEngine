#pragma once
#include "ugepch.h"
#include "glm/glm.hpp"
#include "core/UUID.h"
#include "renderer/VertexArray.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/OrthographicCamera.h"

namespace UGE {

	struct IDComponent {
		
		UUID id = 0;
	};

	struct TransformComponent {

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::mat4& trans)
			:transform(trans)
		{};


		glm::mat4 transform = glm::mat4(1.0f);

		operator glm::mat4() { return transform; };
	};



	struct TagComponent {

		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& name)
			:ComponentName(name) {};

		std::string ComponentName = "default_component";
	};


	struct Mesh2DComponent {

		Mesh2DComponent() = default;
		Mesh2DComponent(const Mesh2DComponent& other) = default;
		Mesh2DComponent(Ref<Shader> shdr, Ref<VertexArray> vtxary, Ref<Texture2D> txtr)
			:Shader(shdr), VertexArray(vtxary), Texture(txtr) {};


		Ref<Shader> Shader;
		Ref<VertexArray> VertexArray;
		Ref<Texture2D> Texture;
	

	};

	struct SpriteRendererComopnent {

		SpriteRendererComopnent() = default;
		SpriteRendererComopnent(const  SpriteRendererComopnent& other) = default;
		SpriteRendererComopnent(Ref<Texture2D> texture)
			:Texture(texture) {};
		SpriteRendererComopnent(const glm::vec4& bgcolor, Ref<Texture2D> texture)
			:BackgroundColor(bgcolor), Texture(texture) {};

		glm::vec4 BackgroundColor = { 1.0f, 1.0f, 1.0f, 1.0f };
		Ref<Texture2D> Texture = nullptr;
	};


	struct CameraComponent
	{
		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;

		CameraComponent(Ref<OrthographicCamera> cemera)
			:Camera(cemera) {};

		Ref<OrthographicCamera> Camera;

	};









}