#include "ugepch.h"
#include "Application.h"
#include "IO/uge_io.h"

#include "glad/glad.h"
#include "platform/openGL/gl_debug.h"
#include "renderer/Renderer.h"

namespace UGE {



	Application* Application::s_Instance = nullptr;

	Application::Application() {
		UGE_CORE_ASSERT(!s_Instance, "Application already exists. ");
		s_Instance = this;

		m_window = std::unique_ptr<BaseWindow>(WindowsWindow::Create());
		m_window->setEventCallback(_UGE_BIND_CALLBACK(Application::onEvent));



		//Temperay code



		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.9f, 0.1f, 0.1f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.7f, 0.8f, 0.1f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.7f, 0.1f, 1.0f
		};

		float square_vertices[3 * 4] = {
			-0.75f, -0.75f, 0,
			-0.75f,  0.75f, 0,
			 0.75f,  0.75f, 0,
			 0.75f, -0.75f, 0
		};
		

		VertexBuffer* vertex_buffer = VertexBuffer::Create(vertices, sizeof(vertices));
		VertexBuffer* square_vb = VertexBuffer::Create(square_vertices, sizeof(square_vertices));;

	
		BufferLayout layout = {
				{ShaderDataType::Float3, "a_position" },
				{ShaderDataType::Float4, "a_color" }
			};

		BufferLayout square_layout = {
				{ShaderDataType::Float3, "a_position" },
		};

		vertex_buffer->setBufferLayout(layout);
		square_vb->setBufferLayout(square_layout);

		int indices[3] = { 0, 1, 2 };
		int square_indices[6] = { 0, 1, 2, 2, 3, 0 };

		IndexBuffer* index_buffer = IndexBuffer::Create(indices, 3);
		IndexBuffer* square_ib = IndexBuffer::Create(square_indices, 6);
		

		m_vertex_array.reset(VertexArray::Create());
		m_vertex_array->AddVertexBuffer(std::shared_ptr<VertexBuffer>(vertex_buffer));
		m_vertex_array->SetIndexBuffer(std::shared_ptr<IndexBuffer>(index_buffer));

		
		m_VAsquare.reset(VertexArray::Create());
		m_VAsquare->AddVertexBuffer(std::shared_ptr<VertexBuffer>(square_vb));
		m_VAsquare->SetIndexBuffer(std::shared_ptr<IndexBuffer>(square_ib));


		ShaderProgramSource src = Shader::ParseFile("C:/Dev/UntitledGameEngine/UntitledGameEngine/Resources/Shaders/testshader.shader");

		ShaderProgramSource blue_src = Shader::ParseFile("C:/Dev/UntitledGameEngine/UntitledGameEngine/Resources/Shaders/blueshader.shader");

		m_shader.reset(Shader::Create(src));
		m_blue_shader.reset(Shader::Create(blue_src));
	

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



			RendererCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			RendererCommand::Clear();

			Renderer::BeginScene();


			m_blue_shader->Bind();
			Renderer::Submit(m_VAsquare);

			m_shader->Bind();
			Renderer::Submit(m_vertex_array);
			

			Renderer::EndScene();
	



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