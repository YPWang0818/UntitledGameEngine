#pragma once

#include "renderer/RendererAPI.h"



namespace UGE {

	class OpenGLRendererAPI : public RendererAPI {

	public:
		virtual void DrawIndexed(const std::shared_ptr<VertexArray> vertex_array)  override ;
		virtual void setClearColor(const glm::vec4& color)  override;
		virtual void Clear() override;

	};


}