#include "ugepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "platform/openGL/OpenGLBuffer.h"

namespace UGE {



	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, const VertexBufferSettings& settings)
	{
		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::API::OpenGL:	return  CreateRef<OpenGLVertexBuffer>(vertices, settings);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}


	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		VertexBufferSettings settings = {BufferUsageHint::Static, size};
		return VertexBuffer::Create(vertices, settings);
	}


	Ref<VertexBuffer> VertexBuffer::Create(const VertexBufferSettings& settings)
	{
		return VertexBuffer::Create(nullptr, settings);
	}



	Ref<IndexBuffer> IndexBuffer::Create(int* indices, const IndexBufferSettings& settings)
	{
		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::API::OpenGL:	return  CreateRef<OpenGLIndexBuffer>(indices, settings);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.")
			return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(int* indices, uint32_t count) {
		IndexBufferSettings settings = { BufferUsageHint::Static, count };

		return IndexBuffer::Create(indices, settings);
	}


	Ref<IndexBuffer> IndexBuffer::Create(const IndexBufferSettings& settings)
	{
		return IndexBuffer::Create(nullptr, settings);
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