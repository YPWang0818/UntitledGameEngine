#pragma once
#include"ugepch.h"
#include "Shader.h"

namespace UGE {

	
	

	struct LayoutElement
	{
		ShaderDataType type;
		std::string name;
		int size;
		int offset;
		bool normalized;

		LayoutElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: type(type), name(name), size(_shader_data_type_size(type)), offset(0), normalized(normalized)
		{
		};

		LayoutElement() = default;
	};



	class BufferLayout {

	public:

		inline const std::vector<LayoutElement>& getLayoutElements() const { return m_layout; };
		inline uint32_t getStride() const { return m_stride; };
		BufferLayout(const std::initializer_list<LayoutElement>& layout);
		BufferLayout() = default;

		std::vector<LayoutElement>::iterator begin() { return m_layout.begin(); };
		std::vector<LayoutElement>::iterator end() { return m_layout.end(); };

		std::vector<LayoutElement>::const_iterator begin() const { return m_layout.begin(); };
		std::vector<LayoutElement>::const_iterator end() const { return m_layout.end(); };
	
	private:

		void _calculate_stride_and_offset();

		std::vector<LayoutElement> m_layout;
		uint32_t m_stride;

	};


	enum class BufferUsageHint {
		Static = 1,
		Dyanmic = 2 
	};

	struct VertexBufferSettings 
	{
		BufferUsageHint hint = BufferUsageHint::Static;
		uint32_t bufferSize = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void setBufferLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getBufferLayout() const = 0 ;
		virtual void setData(void* data, uint32_t size, uint32_t offset = 0) = 0;
	

		//only float will be supported for now.
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, const VertexBufferSettings& settings);
		static Ref<VertexBuffer> Create(const VertexBufferSettings& settings = VertexBufferSettings());


	};


	struct IndexBufferSettings
	{
		BufferUsageHint hint = BufferUsageHint::Static;
		uint32_t bufferCount = 0;
	};


	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual unsigned int getCount() const = 0;

		//only float will be supported for now.
		static Ref<IndexBuffer> Create(int* indices, uint32_t count);
		static Ref<IndexBuffer> Create(int* indices, const IndexBufferSettings& settings);
		static Ref<IndexBuffer> Create( const IndexBufferSettings& settings = IndexBufferSettings());

	};





}