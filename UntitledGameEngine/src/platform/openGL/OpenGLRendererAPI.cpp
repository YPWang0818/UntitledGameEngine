#include "ugepch.h"
#include "platform/openGL/OpenGLRendererAPI.h"
#include "glad/glad.h"
#include "platform/openGL/gl_debug.h"

namespace UGE{

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> vertex_array)
	{
		_GLCALL(
			glDrawElements(GL_TRIANGLES, vertex_array->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
		);
	}

	void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);

	}

}
