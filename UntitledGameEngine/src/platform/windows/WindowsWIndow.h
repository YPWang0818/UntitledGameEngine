#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "core/Core.h"
#include "core/BaseWindow.h"
#include "renderer/GraphicsContex.h"

namespace UGE {

	class  WindowsWindow : public BaseWindow
	{
	public:
		WindowsWindow(const WindowProps& props);
		WindowsWindow(const WindowProps& props, Ref<GraphicsContex> shared_contex);

		virtual ~WindowsWindow();

	
		virtual void onUpdate() override;

		virtual unsigned int getWidth() const override { return m_settings.Width; };
		virtual unsigned int getHight() const override { return m_settings.Hight; };
		virtual const glm::ivec2& getPos() const override { return m_settings.Position; };
		virtual void* getNativeWindow() const override { return m_window; };
		virtual const WindowProps& getWindowProps() const override{ return m_settings; };
		virtual Ref<GraphicsContex> getGraphicsContex() const override { return m_contex; };

		virtual bool isFocused() override;
		virtual bool isMinimized() override;
		virtual bool isVSync() const override;

		virtual void FocusWindow() override ; // Focus the window, if the window is visible and not iconfied. 

		virtual void setSize(unsigned int width, unsigned hight) override;
		virtual void setPos(const glm::ivec2 pos) override;
		virtual void setVSync(bool enabled) override;
		virtual void setVisbility(bool isVisible) override; // Specify if the window is visible to the user or not. 
		virtual void setDecorated(bool isDecorated) override; // Specify if the window has decorations such as a border, a close widget, etc. 
		virtual void setFocusedOnShow(bool isFocusedOnShow) override; // Specify if the window will be focused initially when it is set to visible. 
		virtual void setTopMost(bool isFloating) override; // Specify if the window will always be on top.
		virtual void setTitle(const std::string& title) override;
		virtual void setEventCallback(const EventCallbackFn& callback) override { m_settings.callback_fun = callback; };



	private:
		virtual void Init(const WindowProps& props, Ref<GraphicsContex> shared_contex);
		virtual void ShutDown();

		

	private:

		/* Don't need this part for now. 

		struct WindowInternalData {
			bool isIconfied = false;
			bool isFocused = false;
		};
		WindowInternalData m_data;

		*/

		WindowProps m_settings;
		GLFWwindow* m_window;

		Ref<GraphicsContex> m_contex;

	};



}