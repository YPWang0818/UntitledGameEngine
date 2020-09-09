#include "ugepch.h"
#include "WindowsWindow.h"
#include "events/uge_events.h"
#include "platform/openGL/OpenGLContex.h"

namespace UGE {

	static bool _glfw_initialized = false; // A tag to record if GLFW is initialized.
	static void _glfw_custom_error_callback(int error_code, const char* description) {

		UGE_CORE_ERROR("GLFW error ({0}) {1}", error_code, description);
	};





	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props, nullptr);
	};

	WindowsWindow::WindowsWindow(const WindowProps& props, Ref<GraphicsContex> shared_contex)
	{
		Init(props, shared_contex);
	};

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	};


	 void WindowsWindow::Init(const WindowProps& props, Ref<GraphicsContex> shared_contex) {

		 m_data = props;

		UGE_CORE_INFO("Creating Window: {0} {1} {2}", props.Title, props.Hight, props.Width);

		setVSync(m_data.isVync);
		glfwInitHint(GLFW_VISIBLE, (m_data.isVisble ? GLFW_TRUE : GLFW_FALSE ));
		glfwInitHint(GLFW_DECORATED, (m_data.isDecorated ? GLFW_TRUE : GLFW_FALSE));
		glfwInitHint(GLFW_FOCUSED, (m_data.isFocused ? GLFW_TRUE : GLFW_FALSE));
		glfwInitHint(GLFW_FLOATING, (m_data.isFloating ? GLFW_TRUE : GLFW_FALSE));
		glfwInitHint(GLFW_FOCUS_ON_SHOW, (m_data.isFocusedOnShow ? GLFW_TRUE : GLFW_FALSE));

		if (!(_glfw_initialized))
		{
			int glfw_success = glfwInit();
			UGE_CORE_ASSERT(glfw_success, "Could not initalized glfw!");
			glfwSetErrorCallback(_glfw_custom_error_callback);
			_glfw_initialized = true;

		}

		GLFWwindow* shared_window = nullptr;
		if (!shared_contex) shared_window = (GLFWwindow*)shared_contex->getContexWindow();

		m_window = glfwCreateWindow((int)props.Width, (int)props.Hight, props.Title.c_str(), nullptr, shared_window);

		m_contex = CreateRef<OpenGLContex>(m_window);
		m_contex->Init();

		glfwSetWindowUserPointer(m_window, &m_data);
	

		//set glfw callbacks.

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int hight)
			{
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Hight = hight;

				WindowResizeEvent event(width, hight);
				data.callback_fun(event);

			});
		
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.callback_fun(event);

			});
		
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scan_code, int action, int mods)
			{
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

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

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(c);
			data.callback_fun(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods ){

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
			
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

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x_pos, (float)y_pos);
			data.callback_fun(event);

			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

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

		m_contex->SwapBuffers();

	
		

	};

	 void WindowsWindow::setVSync(bool enabled) {

		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_data.isVync = enabled;
	};

	 bool WindowsWindow::isVSync() const {
		return m_data.isVync;
	}


	 void WindowsWindow::setVisbility(bool isVisible)
	 {
	 }
	 void WindowsWindow::setDecorated(bool isDecorated)
	 {
	 }
	 void WindowsWindow::setFocused(bool isFocused)
	 {
	 }
	 void WindowsWindow::setFocusedOnShow(bool isFocusedOnShow)
	 {
	 }
	 void WindowsWindow::setTopMost(bool isFloating)
	 {
	 }
	 const WindowProps& WindowsWindow::getWindowProps()
	 {	
		 return m_data;
	 };
}