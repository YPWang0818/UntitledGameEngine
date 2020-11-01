#include "ugepch.h"
#include "glm/gtc/matrix_transform.hpp"
#include "EditorLayer.h"

namespace UE {

		UGE::InputHandler& handler = UGE::InputHandler::getInputHandler();

		EditorLayer::EditorLayer()
		:ImguiLayer("Untitled Editor"), m_EditorCamera{ -2.56f, 2.56f, -1.44f, 1.44f }, m_EditorScene("Editor Scene")
		{
			
		};


		void EditorLayer::onAttach()
		{

			UGE::Ref<UGE::Texture2D> logoTexture = UGE::Texture2D::Create("C:/Dev/UntitledGameEngine/Sandbox/Assets/Textures/hazel.png");

			UGE::Ref<UGE::Texture2D> checkerBoardTexture = UGE::Texture2D::Create("C:/Dev/UntitledGameEngine/Sandbox/Assets/Textures/checkerboard.png");

		
			m_EditorScene.CreateEntity("LogoSquare");
			m_EditorScene.CreateEntity("CheckerBoardSquare");

			UGE::Entity logoEnitity = m_EditorScene.GetEntityByTag("LogoSquare");
			UGE::Entity checkerBoardEnitity = m_EditorScene.GetEntityByTag("CheckerBoardSquare");

			logoEnitity.AddComponent<UGE::SpriteRendererComopnent>(logoTexture);
			checkerBoardEnitity.AddComponent<UGE::SpriteRendererComopnent>(checkerBoardTexture);

			UGE::FrameBufferSettings fb_settings = UGE::FrameBufferSettings();
			m_frame_buffer = UGE::FrameBuffer::Create(fb_settings);
		}

		void EditorLayer::onUpdate(UGE::TimeStep ts) 
		{

			if (handler.isKeyDown(UGE_KEY_UP)) m_camera_position.y += m_camera_speed * ts;
			else if (handler.isKeyDown(UGE_KEY_DOWN))  m_camera_position.y -= m_camera_speed * ts;


			if (handler.isKeyDown(UGE_KEY_RIGHT))  m_camera_position.x += m_camera_speed * ts;
			else if (handler.isKeyDown(UGE_KEY_LEFT)) m_camera_position.x -= m_camera_speed * ts;
	

			if (handler.isKeyDown(UGE_KEY_A)) m_camera_rotation += m_camera_rotation_speed * ts;
			else if (handler.isKeyDown(UGE_KEY_D)) m_camera_rotation -= m_camera_rotation_speed * ts;
		

			m_EditorCamera.setPosition(m_camera_position);
			m_EditorCamera.setRotation(m_camera_rotation);


			UGE::RendererCommand::setClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			UGE::RendererCommand::Clear();
			
			BeginUI();
			RenderUI(ts);
			RenderViewport(ts);
			EndUI();
	
	
			
		};

	

		void EditorLayer::RenderViewport(UGE::TimeStep ts)
		{
			m_frame_buffer->Bind();
			m_frame_buffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y, true);

			m_EditorScene.OnSceneUpdate(m_EditorCamera,ts);
			m_frame_buffer->UnBind();

		}

		void EditorLayer::RenderUI(UGE::TimeStep ts)
		{

		

			ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
			ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
				
			window_flags |= ImGuiWindowFlags_NoDocking
				         | ImGuiWindowFlags_NoTitleBar 
				         | ImGuiWindowFlags_NoCollapse  
				         | ImGuiWindowFlags_NoResize 
				         | ImGuiWindowFlags_NoMove
				         | ImGuiWindowFlags_NoBringToFrontOnFocus 
						 | ImGuiWindowFlags_NoNavFocus;


			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);

			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			
					
			ImGui::Begin("Untitled Editor", nullptr, window_flags);
			ImGui::PopStyleVar(3);

			ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			
			ImGui::Begin("ViewPort");
			viewportSize = ImGui::GetContentRegionAvail();
			viewportSize.x = viewportSize.x <= 0 ? 1 : viewportSize.x;
			viewportSize.y = viewportSize.y <= 0 ? 1 : viewportSize.y;
			ImGui::Image((void*)m_frame_buffer->getColorAttachmentID(), viewportSize, { 0, 1 }, { 1, 0 });
			ImGui::End();


			ImGui::End();

	
		}


		void EditorLayer::onDetach()
		{
		
		}

	

	


}