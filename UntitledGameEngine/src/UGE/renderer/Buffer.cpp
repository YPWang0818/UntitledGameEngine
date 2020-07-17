#include "ugepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "platform/openGL/OpenGLBuffer.h"

namespace UGE {


	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
	{
		switch (RendererAPI::getAPI()) 
		{
		case RendererAPI::API::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::API::OpenGL:	return  CreateRef<OpenGLVertexBuffer>(vertices, size);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
			return nullptr;
	}


	Ref<IndexBuffer> IndexBuffer::Create(int* indices, unsigned int size) {

		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::API::OpenGL:	return  CreateRef<OpenGLIndexBuffer>(indices, size);

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