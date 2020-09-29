#include "ugepch.h"
#include "Renderer.h"
#include "FrameBuffer.h"
#include "platform/openGL/OpenGLFrameBuffer.h"


namespace UGE {



	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSettings& settings)
	{
		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::API::OpenGL:	return  CreateRef<OpenGLFrameBuffer>(settings);

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}