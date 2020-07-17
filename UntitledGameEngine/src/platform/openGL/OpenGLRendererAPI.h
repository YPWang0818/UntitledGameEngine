#pragma once

#include "renderer/RendererAPI.h"



namespace UGE {

	class OpenGLRendererAPI : public RendererAPI {

	public:
		virtual void DrawIndexed(const Ref<VertexArray> vertex_array)  override ;
		virtual void setClearColor(const glm::vec4& color)  override;
		virtual void Clear() override;
		virtual void Init() override;
	};


}