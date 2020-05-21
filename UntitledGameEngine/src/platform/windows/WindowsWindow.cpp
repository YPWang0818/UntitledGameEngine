#include "ugepch.h"
#include "WindowsWindow.h"
#include "events/uge_events.h"

namespace UGE {

	static bool _glfw_initialized = false; // A tag to record if GLFW is initialized.
	static void _glfw_custom_error_callback(int error_code, const char* description) {

		UGE_CORE_ERROR("GLFW error ({0}) {1}", error_code, description);
	};

	 BaseWindow* BaseWindow::Create(const WindowProps& props) {
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

		if (!(_glfw_initialized))
		{
			int glfw_success = glfwInit();
			UGE_CORE_ASSERT(glfw_success, "Could not initalized glfw!");
			glfwSetErrorCallback(_glfw_custom_error_callback);
			_glfw_initialized = true;

		}

		m_window = glfwCreateWindow((int)props.Width, (int)props.Hight, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);

		int glad_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		UGE_CORE_ASSERT(glad_success ,"Failed to initialize OpenGL context.");
	

		//set glfw callbacks.

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int hight)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.width = width;
				data.hight = hight;

				WindowResizeEvent event(width, hight);
				data.callback_fun(event);

			});
		
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.callback_fun(event);

			});
		
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scan_code, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {

					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.callback_fun(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.callback_fun(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1); //TODO: retrive repeat count.  
						data.callback_fun(event);
						break;
					}
				};

			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int c) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(c);
			data.callback_fun(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods ){

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			
			switch(action){

				case GLFW_PRESS:
				{	
					MousePressedEvent event(button);
					data.callback_fun(event);
					break;

				}
				case GLFW_RELEASE:
				{
					MouseReleasedEvent event(button);
					data.callback_fun(event);
					break;
				}

			};

			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x_pos, double y_pos) {

			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x_pos, (float)y_pos);
			data.callback_fun(event);

			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.callback_fun(event);

			});

	};

	 void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_window);
	};


	void WindowsWindow::onUpdate()
	{
		
		glfwPollEvents();
		glfwSwapBuffers(m_window);

		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		

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