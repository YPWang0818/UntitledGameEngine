#include "ugepch.h"
#include "ImguiLayer.h"
#include "Imgui.h"
#include "Application.h"
#include "glfw/glfw3.h"
#include "platform/openGL/imgui_opengl_renderer.h"

namespace UGE {
	ImguiLayer::ImguiLayer()
		: Layer("ImGui Layer")
	{
	}

	void ImguiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Set temperary key code mapping
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;


		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImguiLayer::onDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiLayer::onUpdate()
	{
		// setup display size
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::getInstance();
		int w = app.getWindowHandle().getWidth();
		int h = app.getWindowHandle().getHight();

		io.DisplaySize = ImVec2((float)w, (float)h);

		// Setup time step
		float current_time = glfwGetTime();
		io.DeltaTime = m_time > 0.0 ? (current_time - m_time) : (1.0f / 60.0f);
		m_time = current_time;


		// update
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		//show demo window
		bool show_demo_window = true;
		ImGui::ShowDemoWindow(&show_demo_window);
 
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImguiLayer::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.DispatchEvents<KeyPressedEvent>(_UGE_BIND_CALLBACK(ImguiLayer::_KeyCallBack));
		dispatcher.DispatchEvents<KeyReleasedEvent>(_UGE_BIND_CALLBACK(ImguiLayer::_KeyCallBack));
		dispatcher.DispatchEvents<MousePressedEvent>(_UGE_BIND_CALLBACK(ImguiLayer::_MouseButtonCallBack));
		dispatcher.DispatchEvents<MouseReleasedEvent>(_UGE_BIND_CALLBACK(ImguiLayer::_MouseButtonCallBack));
		dispatcher.DispatchEvents<MouseMovedEvent>(_UGE_BIND_CALLBACK(ImguiLayer::_CursorPosCallBack));
		dispatcher.DispatchEvents<MouseScrolledEvent>(_UGE_BIND_CALLBACK(ImguiLayer::_ScrollCallBack));
		//dispatcher.DispatchEvents<KeyCharEvent>(_UGE_BIND_CALLBACK(ImguiLayer::_ScrollCallBack));

	}


	bool ImguiLayer::_KeyCallBack(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (e.getEventType() == EventType::keyPressed) {

			io.KeysDown[e.getKeyCode()] = true;
			return true;
		}
		else if(e.getEventType() == EventType::keyReleased){
			io.KeysDown[e.getKeyCode()] = false;
			return true;
		}

		return false;
	}


	bool ImguiLayer::_MouseButtonCallBack(Event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (e.getEventType() == EventType::mousePressed) {

			io.MouseDown[e.getMosueButton()] = true;
			return true;
		}
		else if (e.getEventType() == EventType::mouseReleased) {
			io.MousesDown[e.getMouseButton()] = false;
			return true;
		}

		return false
	}


	bool ImguiLayer::_CursorPosCallBack(Event& e)
	{
		io.MousePos = ImVec2((float)e.getXPos(), (float)e.getYPos());
		return true;
	}


	bool ImguiLayer::_ScrollCallBack(Event& e)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += (float)e.getxOffset();
		io.MouseWheel += (float)e.getyOffset();


		return true;
	}


	//bool ImguiLayer::_CharCallBack(Event& e){}
}