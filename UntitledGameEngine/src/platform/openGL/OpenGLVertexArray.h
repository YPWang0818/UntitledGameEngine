#pragma once
#include "ugepch.h"
#include "renderer/VertexArray.h"


namespace UGE {

	class OpenGLVertexArray : public VertexArray
	{
	public:

		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void AddVertexBuffer(const Ref<VertexBuffer> vertex_buffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> index_buffer) override ;

		virtual Ref<VertexBuffer>* getVertexBuffers() override { return m_vertex_buffers.data(); };
		virtual IndexBuffer* getIndexBuffer() override { return m_index_buffer.get(); };

	private:
		uint32_t m_rendererID;
		std::vector<Ref<VertexBuffer>> m_vertex_buffers;
		Ref<IndexBuffer> m_index_buffer;
	};




}