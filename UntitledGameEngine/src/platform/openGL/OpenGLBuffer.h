#pragma once
#include "renderer/Buffer.h"


namespace UGE {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertices, const VertexBufferSettings& settings);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void setBufferLayout(const BufferLayout& layout) override { m_layout = layout; };
		virtual const BufferLayout& getBufferLayout() const override { return m_layout; };
		virtual void setData(void* data, uint32_t size, uint32_t offset = 0) override;
	private:
		 uint32_t m_rendererID;
		 VertexBufferSettings m_settings;
		 BufferLayout m_layout;

	};


	class OpenGLIndexBuffer : public IndexBuffer 
	{

	public:
		OpenGLIndexBuffer(int* vertices, const IndexBufferSettings& settings);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual unsigned int getCount() const override { return m_settings.bufferCount; };

	private:
		unsigned int m_rendererID;
		IndexBufferSettings m_settings;

	};


}