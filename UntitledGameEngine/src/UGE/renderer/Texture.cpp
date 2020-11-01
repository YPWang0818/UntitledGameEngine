#include "ugepch.h"
#include "Texture.h"
#include "Renderer.h"
#include "platform/openGL/OpenGLTexture.h"

namespace UGE{




	Ref<Texture2D> Texture2D::Create(uint32_t hight, uint32_t width)
	{
		switch (RendererAPI::getAPI()) {
		case(RendererAPI::API::None): UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case(RendererAPI::API::OpenGL): return CreateRef<OpenGLTexture2D>(hight, width);
		};

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;

	}

	Ref<Texture2D> Texture2D::Create(const std::string filepath)
	{
		switch (RendererAPI::getAPI()) {
		case(RendererAPI::API::None): UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case(RendererAPI::API::OpenGL): return CreateRef<OpenGLTexture2D>(filepath);
		};

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;

	}

}