#pragma once
#include "ugepch.h"
#include "Core.h"
#include "platform/windows/WindowsWindow.h"
#include "events/evt_includes.h"


namespace UGE {
	class UGE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void onEvent(Event& e);
		void Run();

	private:
		bool _CloseWindow(WindowCloseEvent& e);

		std::unique_ptr<BaseWindow> m_window;
		bool m_running = true;

	};

	Application* createApp();
}