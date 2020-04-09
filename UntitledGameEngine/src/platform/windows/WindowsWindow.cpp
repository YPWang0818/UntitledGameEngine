#include "ugepch.h"
#include "WindowsWindow.h"


namespace UGE {

	static bool s_GLFWInitialized = false; // A tag to record if GLFW is initialized.


	BaseWindow* BaseWindow::Create(const WindowProps& prop) {
		return new WindowsWindow()
	};



	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init();
	};

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	};


	virtual void WindowsWindow::Init(const WindowProps& props) {

		m_data.title = props.Title;
		m_data.hight = props.Hight;
		m_data.width = props.Width;
		
		UGE_CORE_INFO("Creating Window: {0} {1} {2}", props.Title, props.Hight, props.Width);

		setVSync(true);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			UGE_CORE_ASSERT(success, "Could not initalized glfw!");
			s_GLFWInitialized = true;

		}

		m_window = glfwCreateWindow((int)props.Width, (int)props.Hight, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &props);

	};

	virtual void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
	};


}