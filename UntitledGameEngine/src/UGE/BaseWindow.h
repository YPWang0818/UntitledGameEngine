#pragma once
#include "ugepch.h"
#include "Core.h"
#include "events/Event.h"

namespace UGE{

	struct  WindowProps {
		
		std::string Title;
		unsigned int Width;
		unsigned int Hight;

		WindowProps(
			std::string title = "Untitled Game Engine",
			unsigned int width = 1280,
			unsigned int hight = 720
			)
			: Title(title), Width(width), Hight(hight)
		{}
	};



	class UGE_API BaseWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~BaseWindow() {} = 0;

		virtual unsigned int getWidth() const  = 0;
		virtual unsigned int getHight() const = 0;

		virtual void Onupdate() = 0;
		virtual void setEventCallback(EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		static BaseWindow* Create(const WindowProps& prop = WindowProps());
			



	};



}