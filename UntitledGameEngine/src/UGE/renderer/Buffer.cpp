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

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(int* indices, unsigned int size) {

		switch (Renderer::getAPI())
		{
		case RendererAPI::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::OpenGL:	return new OpenGLIndexBuffer(indices, size);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.")
			return nullptr;
	}

	


	/****************************** BufferLayout ********************************/

	BufferLayout::BufferLayout(const std::initializer_list<LayoutElement>& layout)
		:m_layout(layout)
	{
		_calculate_stride_and_offset();
	};
	
	void BufferLayout::_calculate_stride_and_offset()
	{

		int offset = 0;

		for (auto& element : m_layout) {

			element.offset = offset;
			offset += _shader_data_type_size(element.type);

		}

		m_stride = offset;
	}

}