#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "core/BaseWindow.h"
#include "renderer/GraphicsContex.h"

namespace UGE {

	class  WindowsWindow : public BaseWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
		WindowsWindow(const WindowProps& props, Ref<GraphicsContex> shared_contex);

		virtual ~WindowsWindow();

		inline unsigned int getWidth() const override { return m_data.Width; };
		inline unsigned int getHight() const override { return m_data.Hight; };
		inline void setEventCallback(const EventCallbackFn& callback) override { m_data.callback_fun = callback; };

		virtual void onUpdate() override;
		virtual void setVSync(bool enabled) override;
		virtual bool isVSync() const override;

		inline virtual void* getNativeWindow() const override {
			return m_window;
		};
		
		virtual void setVisbility(bool isVisible) override; // Specify if the window is visible to the user or not. 
		virtual void setDecorated(bool isDecorated) override; // Specify if the window has decorations such as a border, a close widget, etc. 
		virtual void setFocused(bool isFocused) override; // Specify if the window is focused.
		virtual void setFocusedOnShow(bool isFocusedOnShow) override; // Specify if the window will be focused initially when it is set to visible. 
		virtual void setTopMost(bool isFloating) override; // Specify if the window will always be on top.

		virtual const WindowProps& getWindowProps() override;

	private:
		virtual void Init(const WindowProps& props, Ref<GraphicsContex> shared_contex);
		virtual void ShutDown();

		virtual Ref<GraphicsContex> getGraphicsContex() override { return m_contex; };

	private:

		WindowProps m_data;
		GLFWwindow* m_window;

		Ref<GraphicsContex> m_contex;

	};



}