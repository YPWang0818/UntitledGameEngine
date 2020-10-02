#include "ugepch.h"
#include "ImguiLayer.h"
#include "Imgui.h"
#include "ImguiBackend.h"
#include "core/Application.h"



namespace UGE {
	ImguiLayer::ImguiLayer(const std::string& debug_name)
		: Layer(debug_name)
	{
		ImguiBackend::Init();
		ImGui::StyleColorsDark();
	}
	ImguiLayer::~ImguiLayer()
	{
		ImguiBackend::ShutDown();
	};

	void ImguiLayer::onEvent(Event& e)
	{
		ImguiBackend::OnEvent(e);
	}

	void ImguiLayer::BeginUI(){
		ImguiBackend::NewFrame();	
	}

	void ImguiLayer::EndUI()
	{
		ImGui::Render();
		ImguiBackend::DrawRenderData(ImGui::GetDrawData());
	}

	





}