#include"ugepch.h"
#include "platform/openGL/OpenGLVertexArray.h"
#include "glad/glad.h"
#include "platform/openGL/gl_debug.h"
#include "platform/openGL/OpenGLShader.h"

namespace UGE {
	


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_rendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{

		glDeleteVertexArrays(1, &m_rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_rendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer)
	{

		UGE_CORE_ASSERT(vertex_buffer->getBufferLayout().getLayoutElements().size(), "No Buffer Layout.");

		int idx = 0;
		_GLCALL(
		glBindVertexArray(m_rendererID);
		vertex_buffer->Bind();
		)

		for (const auto& element : vertex_buffer->getBufferLayout()) {

			_GLCALL(

			glEnableVertexAttribArray(idx);
			glVertexAttribPointer(idx,
				_get_element_count(element.type),
				_get_element_opengl_type(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				vertex_buffer->getBufferLayout().getStride(),
				(void*)element.offset);
			)

				idx++;
		};

		m_vertex_buffers.push_back(vertex_buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer)
	{
		_GLCALL(
		glBindVertexArray(m_rendererID);
		index_buffer->Bind();
		)
	}

}