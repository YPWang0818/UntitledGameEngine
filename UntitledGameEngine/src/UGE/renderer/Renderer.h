#pragma once
#include "renderer/RendererAPI.h"
#include "renderer/RendererCommand.h"

namespace UGE {



	class Renderer {

	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertex_array);

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }


	
	};

}