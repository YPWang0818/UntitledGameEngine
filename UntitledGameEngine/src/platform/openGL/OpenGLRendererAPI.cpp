#include "ugepch.h"
#include "platform/openGL/OpenGLRendererAPI.h"
#include "glad/glad.h"
#include "platform/openGL/gl_debug.h"

namespace UGE{

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> vertex_array)
	{

		vertex_array->getIndexBuffer()->Bind();
		for (auto& vt : vertex_array->getVertexBuffers())
		{
			vt->Bind();
		}

		GLCALL(
		glDrawElements(GL_TRIANGLES, vertex_array->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);)
	}

	void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);

	}

	void OpenGLRendererAPI::Init()
	{
		GLCALL(
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);)
	}

}
