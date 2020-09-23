#include "ugepch.h"
#include "ImguiLayer.h"
#include "Imgui.h"
#include "ImguiBackend.h"
#include "core/Application.h"



namespace UGE {
	ImguiLayer::ImguiLayer()
		: Layer("ImGui Layer")
	{};

	void ImguiLayer::onAttach()
	{
		
		Application& app = Application::getInstance();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.getWindowHandle().getNativeWindow());

		
		ImguiBackend::Init();
		ImGui::StyleColorsDark();

	}

	void ImguiLayer::onDetach()
	{
		ImguiBackend::ShutDown();
	}

	void ImguiLayer::onUpdate(TimeStep ts)
	{
		
		Begin();

		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = ts.getSecond();
		bool show_demo_window = true;
		bool show_debug = true;
	

		ImGui::Begin("Hellow World.");
		ImGui::ShowMetricsWindow(&show_debug);
		ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Text("This is some useful text.");
		ImGui::End();

		End();


	}

	void ImguiLayer::onEvent(Event& e)
	{
		ImguiBackend::OnEvent(e);
	}

	void ImguiLayer::Begin(){
		ImguiBackend::NewFrame();	
	}

	void ImguiLayer::End()
	{
		ImGui::Render();
		ImguiBackend::DrawRenderData(ImGui::GetDrawData());
	}

	





}