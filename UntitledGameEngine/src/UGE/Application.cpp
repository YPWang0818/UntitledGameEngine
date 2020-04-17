#include "ugepch.h"
#include "Application.h"
#include "glfw/glfw3.h"


#define _UGE_BIND_CALLBACK(func) std::bind(&func, this , std::placeholders::_1)

namespace UGE {

	Application::Application() {
		m_window = std::unique_ptr<BaseWindow>(WindowsWindow::Create());
		m_window->setEventCallback(_UGE_BIND_CALLBACK(Application::onEvent));
	};

	Application::~Application() {

	};

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.DispatchEvents<WindowCloseEvent>(_UGE_BIND_CALLBACK(Application::_CloseWindow));

		UGE_CORE_TRACE("{0}", e);
	};

	void Application::Run() {
		while (m_running) {

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_window->onUpdate();
		};
	};

	bool Application::_CloseWindow(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}
}