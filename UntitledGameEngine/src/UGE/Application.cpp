#include "ugepch.h"
#include "Application.h"
#include "glfw/glfw3.h"


#define _UGE_BIND_CALLBACK(func) std::bind(&func, this , std::placeholders::_1)

namespace UGE {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		UGE_CORE_ASSERT(!s_Instance, "Application already exists. ");
		s_Instance = this;

		m_window = std::unique_ptr<BaseWindow>(WindowsWindow::Create());
		m_window->setEventCallback(_UGE_BIND_CALLBACK(Application::onEvent));
	};

	Application::~Application() {

	};

	void Application::PushLayer(Layer* layer) {
		m_layer_stack.PushLayer(layer);
		layer->onAttach();
	};

	void Application::PushOverlay(Layer* overlay) {
		m_layer_stack.PushLayer(overlay);
		overlay->onAttach();
	};

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.DispatchEvents<WindowCloseEvent>(_UGE_BIND_CALLBACK(Application::_CloseWindow));
		UGE_CORE_TRACE("{0}", e);

		for (auto it = m_layer_stack.rbegin(); it != m_layer_stack.rend(); ++it) {
			(*it)->onEvent(e);
			if (e.Handled()) {
				break;
			}
		}
	};

	void Application::Run() {
		while (m_running) {

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_layer_stack) {
				layer->onUpdate();
			};

			m_window->onUpdate();
		
		};
	};

	bool Application::_CloseWindow(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}
}