#pragma once

namespace UGE {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		//only float will be supported for now.
		static VertexBuffer* Create(float* vertices, unsigned int size);



	};


	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual unsigned int getCount() const = 0;

		//only float will be supported for now.
		static IndexBuffer* Create(int* indices, unsigned int size);



	};





}