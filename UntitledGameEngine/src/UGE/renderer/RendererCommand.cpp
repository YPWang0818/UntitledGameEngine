#include "ugepch.h"
#include "renderer/RendererCommand.h"
#include "platform/openGL/OpenGLRendererAPI.h"

namespace UGE {

	RendererAPI* RendererCommand::s_API = new OpenGLRendererAPI;


}