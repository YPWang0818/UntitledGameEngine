#include "ugepch.h"
#include "glm/gtc/matrix_transform.hpp"
#include "EditorLayer.h"

namespace UE {

	UGE::InputHandler& handler = UGE::InputHandler::getInputHandler();

	EditorLayer::EditorLayer()
		:Layer("Untitled Editor"), m_camera{ -2.56f, 2.56f, -1.44f, 1.44f }
	{

		float vertices[3 * 7] = {
					-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
					 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
					 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f
		};

		float square_vertices[5 * 4] = {
				-0.5f, -0.5f, 0, 0.0f, 0.0f,
				-0.5f,	0.5f, 0, 0.0f, 1.0f,
				 0.5f,  0.5f, 0, 1.0f, 1.0f,
				 0.5f, -0.5f, 0, 1.0f, 0.0f
		};


		UGE::Ref<UGE::VertexBuffer> vertex_buffer = UGE::VertexBuffer::Create(vertices, sizeof(vertices));
		UGE::Ref<UGE::VertexBuffer> square_vb = UGE::VertexBuffer::Create(square_vertices, sizeof(square_vertices));


		UGE::BufferLayout layout = {
					{UGE::ShaderDataType::Float3, "a_position" },
					{UGE::ShaderDataType::Float4, "a_color" }
		};

		UGE::BufferLayout square_layout = {
			{UGE::ShaderDataType::Float3, "a_position" },
			{UGE::ShaderDataType::Float2, "a_texcoord" }
		};

		vertex_buffer->setBufferLayout(layout);
		square_vb->setBufferLayout(square_layout);

		int indices[3] = { 0, 1, 2 };
		int square_indices[6] = { 0, 1, 2, 2, 3, 0 };

		UGE::Ref<UGE::IndexBuffer> index_buffer = UGE::IndexBuffer::Create(indices, 3);
		UGE::Ref<UGE::IndexBuffer> square_ib = UGE::IndexBuffer::Create(square_indices, 6);


		m_vertex_array = UGE::VertexArray::Create();
		m_vertex_array->AddVertexBuffer(UGE::Ref<UGE::VertexBuffer>(vertex_buffer));
		m_vertex_array->SetIndexBuffer(UGE::Ref<UGE::IndexBuffer>(index_buffer));


		m_VAsquare = UGE::VertexArray::Create();
		m_VAsquare->AddVertexBuffer(square_vb);
		m_VAsquare->SetIndexBuffer(square_ib);


		m_shader = m_shader_library.Load("C:/Dev/UntitledGameEngine/UntitledGameEngine/Resources/Shaders/testshader.shader");
		m_texture_shader = m_shader_library.Load("C:/Dev/UntitledGameEngine/UntitledGameEngine/Resources/Shaders/TextureShader.glsl");

		m_texture_shader->Bind();
		m_texture_shader->setUniformInt("u_texture", 0);

		m_texture = UGE::Texture2D::Create("C:/Dev/UntitledGameEngine/Sandbox/Assets/Textures/hazel.png");
		m_texture->Bind();

		m_cboard_texture = UGE::Texture2D::Create("C:/Dev/UntitledGameEngine/Sandbox/Assets/Textures/checkerboard.png");
		m_cboard_texture->Bind();



		};

		void EditorLayer::onUpdate(UGE::TimeStep ts) 
		{

			//UGE_INFO("TimeStep: {0}, {1}ms", ts.getSecond(), ts.getMillisecond());


			if (handler.isKeyDown(UGE_KEY_UP)) {

				m_camera_position.y += m_camera_speed * ts;

			}
			else if (handler.isKeyDown(UGE_KEY_DOWN)) {

				m_camera_position.y -= m_camera_speed * ts;
			};

			if (handler.isKeyDown(UGE_KEY_RIGHT)) {

				m_camera_position.x += m_camera_speed * ts;

			}
			else if (handler.isKeyDown(UGE_KEY_LEFT)) {

				m_camera_position.x -= m_camera_speed * ts;
			};

			if (handler.isKeyDown(UGE_KEY_A)) {

				m_camera_rotation += m_camera_rotation_speed * ts;

			}
			else if (handler.isKeyDown(UGE_KEY_D)) {

				m_camera_rotation -= m_camera_rotation_speed * ts;
			};

			static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));

			m_texture_shader = m_shader_library.Get("TextureShader.glsl");


			m_camera.setPosition(m_camera_position);
			m_camera.setRotation(m_camera_rotation);

			UGE::RendererCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			UGE::RendererCommand::Clear();

			UGE::Renderer::BeginScene(m_camera);

			for (int y = 0; y < 5; y++) {
				for (int x = 0; x < 5; x++) {
					glm::mat4 transform = glm::translate(glm::mat4(1.0), glm::vec3(0.55f * x, 0.55f * y, 0.0f)) * scale;
					m_cboard_texture->Bind();
					UGE::Renderer::Submit(m_texture_shader, m_VAsquare, transform);
					m_texture->Bind();
					UGE::Renderer::Submit(m_texture_shader, m_VAsquare, transform);
				}
			}

			//UGE::Renderer::Submit(m_shader, m_vertex_array);

			UGE::Renderer::EndScene();

		};

		void EditorLayer::onEvent(UGE::Event& e) 
		{

		};


}