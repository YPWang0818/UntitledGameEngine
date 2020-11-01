#include "ugepch.h"
#include "Application.h"
#include "IO/uge_io.h"
#include "platform/openGL/gl_debug.h"
#include "renderer/Renderer.h"
#include "renderer/Renderer2D.h"
#include "UGE/core/TimeStep.h"

#include "GLFW/glfw3.h"

namespace UGE {



	Application* Application::s_Instance = nullptr;

	Application::Application() 
	{
		UGE_CORE_ASSERT(!s_Instance, "Application already exists. ");
		s_Instance = this;

		m_window = WindowsWindow::Create();
		m_window->setEventCallback(UGE_BIND_CALLBACK(Application::onEvent));

		Renderer::Init();
		Renderer2D::Init();
	

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

		dispatcher.DispatchEvents<WindowCloseEvent>(UGE_BIND_CALLBACK(Application::_CloseWindow));

		//UGE_CORE_TRACE("{0}", e);

		for (auto it = m_layer_stack.rbegin(); it != m_layer_stack.rend(); ++it) {
			(*it)->onEvent(e);
			if (e.Handled()) {
				break;
			}
		}
	};

	void Application::Run() {

		
		
		while (m_running) {

			float  this_frame_time = glfwGetTime();// Moved to Plaform::getTime() eventually.

			TimeStep ts = this_frame_time - m_last_frame_time;

			m_last_frame_time = this_frame_time;


			m_window->onUpdate();

			for (Layer* layer : m_layer_stack) {
				layer->onUpdate(ts);
			};

		
			
		};
	};

	bool Application::_CloseWindow(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}
}