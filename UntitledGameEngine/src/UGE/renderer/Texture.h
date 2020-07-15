#pragma once
#include "ugepch.h"

namespace UGE {


	class Texture {

	public:
		virtual ~Texture() = default;
		virtual uint32_t getHight() const = 0;
		virtual uint32_t getWidth() const  = 0;
		virtual uint32_t getRendererID() const = 0;

		virtual void setData(void* data, uint32_t size) = 0;
		virtual void Bind(uint32_t slot = 0) = 0;

	};


	class Texture2D : public Texture {

	public:
		static Ref<Texture2D> Create(uint32_t hight, uint32_t width);
		static Ref<Texture2D> Create(const std::string filepath);




	};


}