#pragma once
#include "GLFW/glfw3.h"
#include "BaseWindow.h"

namespace UGE {

	class UGE_API WindowsWindow : public BaseWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		virtual inline unsigned int getWidth() const override { return m_data.width; };
		virtual inline unsigned int getHight() const override { return m_data.hight; };
		virtual inline void setEventCallback(EventCallbackFn& callback) override { m_data.func = callback; };

		virtual void onUpdate() override;
		virtual void setVSync(bool enabled) override;
		virtual bool isVSync() const override;

		static WindowsWindow* Create(const WindowProps& props = WindowProps());

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:

		struct WindowData {
			std::string title;
			unsigned int width;
			unsigned int hight;
			bool VSync;
			EventCallbackFn func;
		};

		WindowData m_data;
		GLFWwindow* m_window;


	};



}