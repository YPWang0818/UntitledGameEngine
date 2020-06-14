#pragma once
#include "renderer/RendererAPI.h"
#include "renderer/RendererCommand.h"
#include "renderer/OrthographicCamera.h"

namespace UGE {



	class Renderer {

	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader , const std::shared_ptr<VertexArray>& vertex_array);

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

	private:
		
		struct SceneData 
		{
			glm::mat4 projection_view_matrix;
		};

		static SceneData* m_scndata;
	
	};

}