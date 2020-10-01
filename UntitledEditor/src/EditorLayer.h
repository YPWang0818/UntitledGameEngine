#pragma once

#include "ugepch.h"
#include "UGE.h"


namespace UE {
	
	class EditorLayer : public UGE::Layer
	{
	public:

		EditorLayer();
		//~EditorLayer();

		virtual void onUpdate(UGE::TimeStep ts) override;
		virtual void onEvent(UGE::Event& e) override;
		//virtual void onAttach() override;
		//virtual void onDetach() override;

	private:

		UGE::Ref<UGE::VertexArray> m_vertex_array;
		UGE::Ref<UGE::VertexArray> m_VAsquare;
		UGE::Ref<UGE::Shader> m_shader;
		UGE::Ref<UGE::Shader> m_texture_shader;
		UGE::Ref<UGE::Texture2D> m_texture;
		UGE::Ref<UGE::Texture2D> m_cboard_texture;
		UGE::OrthographicCamera m_camera;
		UGE::ShaderLibrary m_shader_library;

		glm::vec3 m_camera_position = { 0, 0, 0 };
		float m_camera_speed = 3.0f;
		float m_camera_rotation = 0.0f;
		float m_camera_rotation_speed = 1.0f;

	};
}