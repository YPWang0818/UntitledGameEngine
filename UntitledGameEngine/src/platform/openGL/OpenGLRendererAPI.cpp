#include "ugepch.h"
#include "platform/openGL/OpenGLRendererAPI.h"
#include "glad/glad.h"
#include "platform/openGL/gl_debug.h"

namespace UGE{

	void static  _opengl_error_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH: UGE_CORE_ERROR("OpenGL Error: {0}", message); UGE_CORE_ASSERT(false, "");
			break;
		case GL_DEBUG_SEVERITY_MEDIUM: UGE_CORE_WARN("OpenGL Warning: {0}", message);
			break;
		case GL_DEBUG_SEVERITY_LOW: UGE_CORE_INFO("OpenGL Message: {0}", message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:UGE_CORE_TRACE("OpenGL Message: {0}", message);
			break;

		}
	};


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
		
		glDebugMessageCallback(UGE::_opengl_error_callback, nullptr);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}

}
