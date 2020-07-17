#include "ugepch.h"
#include "ImguiLayer.h"
#include "Imgui.h"
#include "core/Application.h"
#include "IO/uge_io.h"
#include "platform/openGL/imgui_opengl_renderer.h"

namespace UGE {
	ImguiLayer::ImguiLayer()
		: Layer("ImGui Layer")
	{};

	void ImguiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Set temperary key code mapping
		io.KeyMap[ImGuiKey_Tab] = UGE_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = UGE_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = UGE_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = UGE_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = UGE_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = UGE_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = UGE_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = UGE_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = UGE_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = UGE_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = UGE_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = UGE_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = UGE_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = UGE_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = UGE_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = UGE_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = UGE_KEY_A;
		io.KeyMap[ImGuiKey_C] = UGE_KEY_C;
		io.KeyMap[ImGuiKey_V] = UGE_KEY_V;
		io.KeyMap[ImGuiKey_X] = UGE_KEY_X;
		io.KeyMap[ImGuiKey_Y] = UGE_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = UGE_KEY_Z;


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
		bool show_demo_window = false;
		ImGui::ShowDemoWindow(&show_demo_window);
 
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImguiLayer::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.DispatchEvents<KeyPressedEvent>(UGE_BIND_CALLBACK(ImguiLayer::_KeyPressedCallBack));
		dispatcher.DispatchEvents<KeyReleasedEvent>(UGE_BIND_CALLBACK(ImguiLayer::_KeyReleasedCallBack));
		dispatcher.DispatchEvents<MousePressedEvent>(UGE_BIND_CALLBACK(ImguiLayer::_MousePressedCallBack));
		dispatcher.DispatchEvents<MouseReleasedEvent>(UGE_BIND_CALLBACK(ImguiLayer::_MouseReleasedCallBack));
		dispatcher.DispatchEvents<MouseMovedEvent>(UGE_BIND_CALLBACK(ImguiLayer::_CursorPosCallBack));
		dispatcher.DispatchEvents<MouseScrolledEvent>(UGE_BIND_CALLBACK(ImguiLayer::_ScrollCallBack));
		dispatcher.DispatchEvents<KeyTypedEvent>(UGE_BIND_CALLBACK(ImguiLayer::_CharCallBack));

	}

	static inline void  _update_control_keys(ImGuiIO& io) {



		//TODO: repace costum keycode.
		io.KeyCtrl = io.KeysDown[UGE_KEY_LEFT_CONTROL] || io.KeysDown[UGE_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[UGE_KEY_LEFT_SHIFT] || io.KeysDown[UGE_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[UGE_KEY_LEFT_ALT] || io.KeysDown[UGE_KEY_RIGHT_ALT];
	};


	bool ImguiLayer::_KeyPressedCallBack(KeyPressedEvent& e)
	{	
		UGE_CORE_ASSERT((e.getEventType() == EventType::keyPressed), "Incorrect event handling");

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = true;
		_update_control_keys(io);

		return true;
	}

	bool ImguiLayer::_KeyReleasedCallBack(KeyReleasedEvent& e) {

		UGE_CORE_ASSERT((e.getEventType() == EventType::keyReleased), "Incorrect event handling");

		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.getKeyCode()] = false;
		_update_control_keys(io);

		return true;
	}

	bool ImguiLayer::_CharCallBack(KeyTypedEvent& e) {

		UGE_CORE_ASSERT((e.getEventType() == EventType::keyTyped), "Incorrect event handling");

		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.getKeyCode());
		_update_control_keys(io);

		return true;
	}

	bool ImguiLayer::_MousePressedCallBack(MousePressedEvent& e)
	{
		UGE_CORE_ASSERT((e.getEventType() == EventType::mousePressed), "Incorrect event handling");

		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMosueButton()] = true;
		return true;
	};


	bool ImguiLayer::_MouseReleasedCallBack(MouseReleasedEvent& e) {

		UGE_CORE_ASSERT((e.getEventType() == EventType::mouseReleased), "Incorrect event handling");
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.getMosueButton()] = false;
		return true;
	}


	bool ImguiLayer::_CursorPosCallBack(MouseMovedEvent& e)
	{
		UGE_CORE_ASSERT((e.getEventType() == EventType::mouseMoved), "Incorrect event handling");

		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2((float)e.getXPos(), (float)e.getYPos());
		return true;
	}


	bool ImguiLayer::_ScrollCallBack(MouseScrolledEvent& e)
	{

		UGE_CORE_ASSERT((e.getEventType() == EventType::mouseScrolled), "Incorrect event handling");

		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += (float)e.getxOffset();
		io.MouseWheel += (float)e.getyOffset();


		return true;
	}





	//bool ImguiLayer::_CharCallBack(Event& e){}
}