#include "ugepch.h"
#include "glm/gtc/matrix_transform.hpp"
#include "EditorLayer.h"

namespace UE {

		UGE::InputHandler& handler = UGE::InputHandler::getInputHandler();

		EditorLayer::EditorLayer()
		:ImguiLayer("Untitled Editor"), m_camera{ -2.56f, 2.56f, -1.44f, 1.44f }
		{
			
		};


		void EditorLayer::onAttach()
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


			UGE::FrameBufferSettings fb_settings = UGE::FrameBufferSettings();
			m_frame_buffer = UGE::FrameBuffer::Create(fb_settings);

		}

		void EditorLayer::onUpdate(UGE::TimeStep ts) 
		{

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

			m_texture_shader = m_shader_library.Get("TextureShader.glsl");


			m_camera.setPosition(m_camera_position);
			m_camera.setRotation(m_camera_rotation);


			UGE::RendererCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			UGE::RendererCommand::Clear();
			
		

	
			BeginUI();

			//ImGui::ShowDemoWindow(&demo);




			bool dockspace_test = true;
			static bool opt_fullscreen_persistant = true;
			bool opt_fullscreen = opt_fullscreen_persistant;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

			// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
			// because it would be confusing to have two docking targets within each others.
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
			if (opt_fullscreen)
			{
				ImGuiViewport* viewport = ImGui::GetMainViewport();
				ImGui::SetNextWindowPos(viewport->GetWorkPos());
				ImGui::SetNextWindowSize(viewport->GetWorkSize());
				ImGui::SetNextWindowViewport(viewport->ID);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
				window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
				window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			}

			// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background 
			// and handle the pass-thru hole, so we ask Begin() to not render a background.
			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

			// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
			// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
			// all active windows docked into it will lose their parent and become undocked.
			// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
			// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &dockspace_test, window_flags);
			ImGui::PopStyleVar();

			if (opt_fullscreen)
				ImGui::PopStyleVar(2);

			// DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			else
			{
				UGE_WARN("Docking not enabled");
			}

			

			ImGui::Begin("ViewPort");

			m_frame_buffer->Bind();

			ImVec2 viewportSize = ImGui::GetContentRegionAvail();
			m_frame_buffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y, true);
			RenderViewport(ts);
			m_frame_buffer->UnBind();

			ImGui::Image((void*)m_frame_buffer->getColorAttachmentID(), viewportSize, { 0, 1 }, { 1, 0 });
			ImGui::End();

			ImGui::End();


			EndUI();
			
		};

	



		void EditorLayer::RenderViewport(UGE::TimeStep ts)
		{
			static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
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

			UGE::Renderer::EndScene();

		}


		void EditorLayer::onDetach()
		{
		
		}

	

	


}