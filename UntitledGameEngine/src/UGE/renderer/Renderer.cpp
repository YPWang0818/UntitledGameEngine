#include "ugepch.h"
#include "Renderer.h"

namespace UGE {
	void Renderer::BeginScene()
	{
	};

	void Renderer::EndScene()
	{
	};

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertex_array)
	{
		vertex_array->Bind();
		RendererCommand::DrawIndexed(vertex_array);
	}
}