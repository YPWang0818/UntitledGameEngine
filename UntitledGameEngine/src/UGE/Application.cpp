#include "ugepch.h"
#include "Application.h"


namespace UGE {

	Application::Application() {
		m_window = WindowsWindow::Create();
	};

	Application::~Application() {
		delete m_window;
	};

	void Application::Run() {
		while (m_running) {
			m_window->onUpdate();
		};
	};
}