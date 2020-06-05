#include "ugepch.h"
#include "Application.h"
#include "IO/uge_io.h"

#include "glad/glad.h"
#include "platform/openGL/gl_debug.h"

namespace UGE {



	Application* Application::s_Instance = nullptr;

	Application::Application() {
		UGE_CORE_ASSERT(!s_Instance, "Application already exists. ");
		s_Instance = this;

		m_window = std::unique_ptr<BaseWindow>(WindowsWindow::Create());
		m_window->setEventCallback(_UGE_BIND_CALLBACK(Application::onEvent));



		//Temperay code



		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.3f, 0.1f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.7f, 0.8f, 0.1f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.8f, 0.1f, 0.9f, 1.0f
		};

		m_vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_vertex_buffer->Bind();
	
		BufferLayout layout = {
				{ShaderDataType::Float3, "a_position" },
				{ShaderDataType::Float4, "a_color" }
			};

	
		int indices[3] = { 0, 1, 2 };

		m_index_buffer.reset(IndexBuffer::Create(indices, 3));
		m_index_buffer->Bind();



		m_vertex_array.reset(VertexArray::Create());
		m_vertex_array->Bind();
		m_vertex_array->AddVertexBuffer(m_vertex_buffer);
		m_vertex_array->SetIndexBuffer(m_index_buffer);

		m_vertex_buffer->setBufferLayout(layout);

		ShaderProgramSource src = Shader::ParseFile("C:/Dev/UntitledGameEngine/UntitledGameEngine/Resources/Shaders/testshader.shader");
		m_shader.reset(Shader::Create(src));
		m_shader->Bind();

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

			//temperary code
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//m_vertex_buffer->Bind();
			//m_index_buffer->Bind();
			m_shader->Bind();

			glDrawElements(GL_TRIANGLES, m_index_buffer->getCount(), GL_UNSIGNED_INT, nullptr);


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