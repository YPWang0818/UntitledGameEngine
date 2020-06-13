#include "ugepch.h"
#include "VertexArray.h"
#include "renderer/Renderer.h"
#include "platform/openGL/OpenGLVertexArray.h"

namespace UGE {

	VertexArray* VertexArray::Create() {


		switch (RendererAPI::getAPI())
		{
		case RendererAPI::API::None:		UGE_CORE_ASSERT(false, "RendererAPI::None is not supported.") return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexArray();

		}

		UGE_CORE_ASSERT(false, "Unknown renderer API.");
		return nullptr;
	}

}