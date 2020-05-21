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
	}

	void OpenGLContex::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}