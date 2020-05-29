#pragma once
#include "renderer/Buffer.h"


namespace UGE {

	class OpenGLVertexBuffer : public VertexBuffer {

	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

	private:
		unsigned int m_rendererID;

	};


	class OpenGLIndexBuffer : public IndexBuffer 
	{

	public:
		OpenGLIndexBuffer(int* vertices, unsigned int size);
		~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual unsigned int getCount() const override { return m_count; };

	private:
		unsigned int m_rendererID;
		unsigned int m_count;

	};


}