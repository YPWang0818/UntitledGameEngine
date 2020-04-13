#pragma once
#include "ugepch.h"
#include "Core.h"
#include "platform/windows/WindowsWindow.h"

namespace UGE {
	class UGE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();

	private:
		WindowsWindow* m_window;
		bool m_running = true;

	};

	Application* createApp();
}