#pragma once
#include "ugepch.h"
#include "Core.h"
#include "events/Event.h"

namespace UGE{



	struct  WindowProps {
		
		std::string Title;
		unsigned int Width;
		unsigned int Hight;

		bool isVisble = true;
		bool isDecorated = true;
		bool isFocused = true;
		bool isFocusedOnShow = true;
		bool isFloating = false;
		bool isVync = true;

		WindowProps(
			std::string title = "Untitled Game Engine",
			unsigned int width = 1280,
			unsigned int hight = 720
			)
			: Title(title), Width(width), Hight(hight)
		{}
	};



	class  BaseWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~BaseWindow() {};

		virtual unsigned int getWidth() const  = 0;
		virtual unsigned int getHight() const = 0;

		virtual void onUpdate() = 0;
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;
		virtual void* getNativeWindow() const = 0;
		static std::shared_ptr<BaseWindow> Create(const WindowProps& = WindowProps());

		virtual void setVisbility(bool isVisible) = 0; // Specify if the window is visible to the user or not. 
		virtual void setDecorated(bool isDecorated) = 0; // Specify if the window has decorations such as a border, a close widget, etc. 
		virtual void setFocused(bool isFocused) = 0; // Specify if the window is focused.
		virtual void setFocusedOnShow(bool isFocusedOnShow) = 0; // Specify if the window will be focused initially when it is set to visible. 
		virtual void setTopMost(bool isFloating) = 0; // Specify if the window will always be on top.

		virtual const WindowProps& getWindowProps() = 0;


	};

	#define UGE_USE_GLFW 

	Ref<BaseWindow> BaseWindow::Create(const WindowProps& props) {

		#if defined (UGE_USE_GLFW)
			return CreateRef<WindowsWindow>(props);
		#else
			UGE_CORE_ASSERT(false, "UGE currently only support GLFW.");
			return nullptr;
		#endif
	};

}