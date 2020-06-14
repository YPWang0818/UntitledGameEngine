#include "ugepch.h"
#include "Renderer.h"

namespace UGE {

	Renderer::SceneData* Renderer::m_scndata = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_scndata->projection_view_matrix = camera.getProjectionViewMatrix();
	};

	void Renderer::EndScene()
	{
	};

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array)
	{
		vertex_array->Bind();
		shader->Bind();
		shader->setUniformMat4("u_ProjectionView", m_scndata->projection_view_matrix);
		RendererCommand::DrawIndexed(vertex_array);
	}
}