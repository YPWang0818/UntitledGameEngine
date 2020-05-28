#pragma once

namespace UGE {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer();
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		//only float will be supported for now.
		static VertexBuffer* Create(float* vertices, unsigned int size);



	};


	class IndexBuffer {
	public:
		virtual ~IndexBuffer();
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual unsigned int getCount() const = 0;

		//only float will be supported for now.
		static IndexBuffer* Create(float* vertices, unsigned int size);



	};





}