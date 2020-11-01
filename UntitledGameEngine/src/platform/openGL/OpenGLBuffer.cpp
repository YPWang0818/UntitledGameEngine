#include"ugepch.h"
#include "glad/glad.h"
#include "gl_debug.h"
#include "OpenGLBuffer.h"

namespace UGE {



	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, const VertexBufferSettings& settings)
		:m_settings(settings)
	{

		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, settings.bufferSize, vertices,( settings.hint == BufferUsageHint::Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
		

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::setData(void* data, uint32_t size, uint32_t offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)offset, (GLsizeiptr)size, data);
	}


	///// Index Buffer 

	OpenGLIndexBuffer::OpenGLIndexBuffer(int* indices, const IndexBufferSettings& settings)
		:m_settings(settings)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, settings.bufferCount * sizeof(unsigned int), indices, (settings.hint == BufferUsageHint::Static ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}