#include "ugepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "platform/openGL/OpenGLBuffer.h"

namespace UGE {


	VertexBuffer* VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (Renderer::getAPI()) 
		{
		case RendererAPI::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLVertexBuffer(vertices, size);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.")
			return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(float* vertices, unsigned int size) {

		switch (Renderer::getAPI())
		{
		case RendererAPI::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(vertices, size);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.")
			return nullptr;
	}
}