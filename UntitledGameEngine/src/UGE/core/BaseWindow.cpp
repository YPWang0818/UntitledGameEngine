#include "ugepch.h"
#include "BaseWindow.h"
#include "platform/windows/WindowsWindow.h"

namespace UGE {



	#define UGE_USE_GLFW 

	Ref<BaseWindow> BaseWindow::Create(const WindowProps& props, Ref<GraphicsContex> shared_contex) {

		#if defined (UGE_USE_GLFW)
		return CreateRef<WindowsWindow>(props, shared_contex);
		#else
		UGE_CORE_ASSERT(false, "UGE currently only support GLFW.");
		return nullptr;
		#endif
	};


	Ref<BaseWindow> BaseWindow::Create(const WindowProps& props) {

		#if defined (UGE_USE_GLFW)
		return CreateRef<WindowsWindow>(props);
		#else
		UGE_CORE_ASSERT(false, "UGE currently only support GLFW.");
		return nullptr;
		#endif
	};
}