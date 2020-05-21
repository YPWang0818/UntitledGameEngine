#pragma once

#include "renderer/GraphicsContex.h"

struct GLFWwindow;

namespace UGE {


	class OpenGLContex : public GraphicsContex
	{
	public:
		OpenGLContex(GLFWwindow* window_handle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_window;
	};


};