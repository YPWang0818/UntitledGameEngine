#pragma once
#include "ugepch.h"
#include "renderer/Buffer.h"

namespace UGE {


	class VertexArray 
	{
	public:
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void AddVertexBuffer(const Ref<VertexBuffer> vertex_buffer ) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> index_buffer) = 0;
		virtual std::vector<Ref<VertexBuffer>> getVertexBuffers() = 0;
		virtual IndexBuffer* getIndexBuffer() = 0;

		static Ref<VertexArray> Create();



	};



}