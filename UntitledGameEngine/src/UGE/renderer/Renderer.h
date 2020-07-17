#pragma once
#include "renderer/RendererAPI.h"
#include "renderer/RendererCommand.h"
#include "renderer/OrthographicCamera.h"

namespace UGE {



	class Renderer {

	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader , const Ref<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

		static void Init();

	private:
		
		struct SceneData 
		{
			glm::mat4 projection_view_matrix;
		};

		static SceneData* m_scndata;
	
	};

}