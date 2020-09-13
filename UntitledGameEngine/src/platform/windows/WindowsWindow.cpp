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
	}

	void WindowsWindow::setSize(unsigned int width, unsigned hight)
	{
		glfwSetWindowSize(m_window, width, hight);

	}
	void WindowsWindow::setPos(const glm::ivec2 pos)
	{
		glfwSetWindowPos(m_window, pos.x, pos.y);

	};




	void WindowsWindow::Init(const WindowProps& props, Ref<GraphicsContex> shared_contex) {

		m_settings = props;

		UGE_CORE_INFO("Creating Window: {0} {1} {2}", props.Title, props.Hight, props.Width);

		setVSync(m_settings.isVync);
		glfwInitHint(GLFW_VISIBLE, (m_settings.isVisble ? GLFW_TRUE : GLFW_FALSE));
		glfwInitHint(GLFW_DECORATED, (m_settings.isDecorated ? GLFW_TRUE : GLFW_FALSE));
		glfwInitHint(GLFW_FOCUSED, (m_settings.isFocusedOnCreate ? GLFW_TRUE : GLFW_FALSE));
		glfwInitHint(GLFW_FLOATING, (m_settings.isFloating ? GLFW_TRUE : GLFW_FALSE));
		glfwInitHint(GLFW_FOCUS_ON_SHOW, (m_settings.isFocusedOnShow ? GLFW_TRUE : GLFW_FALSE));

		if (!(_glfw_initialized))
		{
			int glfw_success = glfwInit();
			UGE_CORE_ASSERT(glfw_success, "Could not initalized glfw!");
			glfwSetErrorCallback(_glfw_custom_error_callback);
			_glfw_initialized = true;

		}

		GLFWwindow* shared_window = nullptr;
		if (shared_contex) shared_window = (GLFWwindow*)shared_contex->getContexWindow();

		m_window = glfwCreateWindow((int)props.Width, (int)props.Hight, props.Title.c_str(), nullptr, shared_window);
		setPos(props.Position);

		m_contex = CreateRef<OpenGLContex>(m_window);
		m_contex->Init();


		glfwSetWindowUserPointer(m_window, &m_settings);


		//set glfw callbacks.

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int hight)
			{
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Hight = hight;

				WindowResizeEvent event(width, hight);

				event.WindowHandle.reset((void*)window);

				data.callback_fun(event);

			});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos) {

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
			data.Position = glm::ivec2(xpos, ypos);

			WindowMovedEvent event(xpos, ypos);
			event.WindowHandle.reset((void*)window);
			data.callback_fun(event);

			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			event.WindowHandle.reset((void*)window);
			data.callback_fun(event);

			});

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused) {

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

			if (focused)
			{
				WindowFocusEvent event;
				event.WindowHandle.reset((void*)window);
				data.callback_fun(event);
			}
			else
			{
				WindowLostFocusEvent event;
				event.WindowHandle.reset((void*)window);
				data.callback_fun(event);
			};
			
			});

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scan_code, int action, int mods)
			{
				WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

				switch (action) {

				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					event.WindowHandle.reset((void*)window);
					data.callback_fun(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					event.WindowHandle.reset((void*)window);
					data.callback_fun(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1); //TODO: retrive repeat count.  
					event.WindowHandle.reset((void*)window);
					data.callback_fun(event);
					break;
				}
				};

			});

		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int c) {

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(c);
			event.WindowHandle.reset((void*)window);
			data.callback_fun(event);
			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

			switch (action) {

			case GLFW_PRESS:
			{
				MousePressedEvent event(button);
				event.WindowHandle.reset((void*)window);
				data.callback_fun(event);
				break;

			}
			case GLFW_RELEASE:
			{
				MouseReleasedEvent event(button);
				event.WindowHandle.reset((void*)window);
				data.callback_fun(event);
				break;
			}

			};

			});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x_pos, double y_pos) {

			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)x_pos, (float)y_pos);
			event.WindowHandle.reset((void*)window);
			data.callback_fun(event);

			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			event.WindowHandle.reset((void*)window);

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
		m_settings.isVync = enabled;
	};

	bool WindowsWindow::isVSync() const {
		return m_settings.isVync;
	}

	void WindowsWindow::setVisbility(bool isVisible)
	{
		isVisible ? glfwShowWindow(m_window) : glfwHideWindow(m_window);
		m_settings.isVisble = isVisible;
	};

	void WindowsWindow::setDecorated(bool isDecorated)
	{
		isDecorated ? glfwSetWindowAttrib(m_window, GLFW_DECORATED, GL_TRUE) : glfwSetWindowAttrib(m_window, GLFW_DECORATED, GL_FALSE);
		m_settings.isDecorated = isDecorated;
	}

	bool WindowsWindow::isFocused()
	{
		return (bool)glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
	}

	bool WindowsWindow::isMinimized()
	{
		return (bool)glfwGetWindowAttrib(m_window, GLFW_ICONIFIED);
	}

	void WindowsWindow::FocusWindow()
	{
		glfwFocusWindow(m_window);
	}

	void WindowsWindow::setFocusedOnShow(bool isFocusedOnShow)
	{
		isFocusedOnShow ? glfwSetWindowAttrib(m_window, GLFW_FOCUS_ON_SHOW, GL_TRUE) : glfwSetWindowAttrib(m_window, GLFW_FOCUS_ON_SHOW, GL_FALSE);
		m_settings.isFocusedOnShow = isFocusedOnShow;
	}

	void WindowsWindow::setTopMost(bool isFloating)
	{
		isFloating ? glfwSetWindowAttrib(m_window, GLFW_FLOATING, GL_TRUE) : glfwSetWindowAttrib(m_window, GLFW_FLOATING, GL_FALSE);
		m_settings.isFloating = isFloating;
	}

	void WindowsWindow::setTitle(const std::string& title)
	{
		m_settings.Title = title;
		glfwSetWindowTitle(m_window, title.c_str());
	}

}