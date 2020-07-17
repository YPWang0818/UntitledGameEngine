#pragma once

#include "renderer/RendererAPI.h"


namespace UGE {

	class RendererCommand {

	public:
		inline static void DrawIndexed(const Ref<VertexArray>& vertex_array)
		{		
			s_API->DrawIndexed(vertex_array);
		};

		static inline void setClearColor(const glm::vec4& color)
		{
			s_API->setClearColor(color);
		};
		static inline void Clear() {
			s_API->Clear();
		};

		static void Init() {

			s_API->Init();
		}


	private:
		static RendererAPI* s_API;


	};



}