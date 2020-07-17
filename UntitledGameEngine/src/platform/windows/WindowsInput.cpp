#include "ugepch.h"
#include "WindowsInput.h"
#include "core/Application.h"
#include "GLFW/glfw3.h"

namespace UGE {

	std::shared_ptr<InputHandler> InputHandler::s_instance = std::make_shared<WindowsInput>();

	bool WindowsInput::_impel_is_key_down(int key)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindowHandle().getNativeWindow());

		int status = glfwGetKey(window, key);

		return (status == GLFW_PRESS) || (status == GLFW_REPEAT);
	};

	bool WindowsInput::_impel_is_mouse_button_down(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindowHandle().getNativeWindow());

		int status = glfwGetMouseButton(window, button);

		return (status == GLFW_PRESS);
	}

	glm::vec2 WindowsInput::_impel_get_cursor_pos()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::getInstance().getWindowHandle().getNativeWindow());

		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);

		return { (float)x_pos, (float)y_pos };
	}


}
