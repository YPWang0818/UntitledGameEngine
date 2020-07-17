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

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		vertex_array->Bind();
		shader->Bind();
		shader->setUniformMat4("u_ProjectionView", m_scndata->projection_view_matrix);
		shader->setUniformMat4("u_Model", transform);
		RendererCommand::DrawIndexed(vertex_array);
	}

	void Renderer::Init() {

		RendererCommand::Init();
	}
}