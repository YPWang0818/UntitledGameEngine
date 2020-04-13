#include "ugepch.h"
#include "WindowsWindow.h"


namespace UGE {

	static bool s_GLFWInitialized = false; // A tag to record if GLFW is initialized.


	 WindowsWindow* WindowsWindow::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	};



	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	};

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	};


	 void WindowsWindow::Init(const WindowProps& props) {

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
		glfwSetWindowUserPointer(m_window, &m_data);

	};

	 void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	};


	void WindowsWindow::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
		

	};

	 void WindowsWindow::setVSync(bool enabled) {

		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_data.VSync = enabled;
	};

	 bool WindowsWindow::isVSync() const {
		return m_data.VSync;
	};
}