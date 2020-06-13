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
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertex_buffer ) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& index_buffer) = 0;
		virtual std::shared_ptr<VertexBuffer>* getVertexBuffers() = 0;
		virtual IndexBuffer* getIndexBuffer() = 0;

		static VertexArray* Create();



	};



}