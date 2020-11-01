#pragma once

#include "ugepch.h"
#include "UGE.h"
#include "imgui.h"

namespace UE {
	
	class EditorLayer : public UGE::ImguiLayer
	{
	public:

		EditorLayer();
		~EditorLayer() = default;

		virtual void onUpdate(UGE::TimeStep ts) override;
		virtual void onAttach() override;
		virtual void onDetach() override;

		void RenderViewport(UGE::TimeStep ts);
		void RenderUI(UGE::TimeStep ts);

	private:
		
		UGE::Scene m_EditorScene;
		UGE::Ref<UGE::FrameBuffer> m_frame_buffer;
		UGE::OrthographicCamera m_EditorCamera;
		UGE::ShaderLibrary m_shader_library;

		glm::vec3 m_camera_position = { 0, 0, 0 };
		float m_camera_speed = 3.0f;
		float m_camera_rotation = 0.0f;
		float m_camera_rotation_speed = 1.0f;

		ImVec2 viewportSize;


	};
}