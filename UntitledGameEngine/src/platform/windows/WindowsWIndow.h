#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "BaseWindow.h"

namespace UGE {

	class UGE_API WindowsWindow : public BaseWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		inline unsigned int getWidth() const override { return m_data.width; };
		inline unsigned int getHight() const override { return m_data.hight; };
		inline void setEventCallback(const EventCallbackFn& callback) override { m_data.callback_fun = callback; };

		virtual void onUpdate() override;
		virtual void setVSync(bool enabled) override;
		virtual bool isVSync() const override;

		inline virtual void* getNativeWindow() const override {
			return m_window;
		};
		//static WindowsWindow* Create(const WindowProps& props = WindowProps());

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int hight;
			bool VSync;
			EventCallbackFn callback_fun;
		};

		WindowData m_data;
		GLFWwindow* m_window;


	};



}