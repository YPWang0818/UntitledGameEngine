#include "ugepch.h"
#include "OpenGLContex.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace UGE {

	OpenGLContex::OpenGLContex(GLFWwindow* window_handle)
		: m_window(window_handle)
	{
		
	}

	void OpenGLContex::Init()
	{
		glfwMakeContextCurrent(m_window);
		int glad_success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UGE_CORE_ASSERT(glad_success, "Failed to initialize OpenGL context.");

		UGE_CORE_INFO("OpenGL Render: {0}", glGetString(GL_RENDERER));
		UGE_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
	}

	void* OpenGLContex::getContexWindow() {
		return (void*)m_window;
	}

	void OpenGLContex::makeContexCurrent()
	{
		glfwMakeContextCurrent(m_window);
	}

	void OpenGLContex::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}