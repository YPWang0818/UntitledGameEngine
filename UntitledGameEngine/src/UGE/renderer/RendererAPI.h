#pragma once
#include "VertexArray.h"
#include "glm/glm.hpp"

namespace UGE {


	class RendererAPI {

	public:
		enum API {
			None = 0,
			OpenGL = 1
		};

		static inline API getAPI() { return s_rendererAPI; };

		virtual void DrawIndexed(const std::shared_ptr<VertexArray> vertex_array ) = 0;
		virtual void setClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

	private:
		static API s_rendererAPI;

	};

}