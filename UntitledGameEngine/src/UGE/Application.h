#pragma once
#include "ugepch.h"
#include "Core.h"
#include "Layer.h"
#include "LayersStack.h"
#include "platform/windows/WindowsWindow.h"
#include "events/uge_events.h"
#include "renderer/Buffer.h"

namespace UGE {

	// This class is a singleton.
	class  Application
	{
	public:

		inline static Application& getInstance() {
			return *s_Instance;
		};
		void operator=(const Application&) = delete;

		Application();
		virtual ~Application();

		inline BaseWindow&  getWindowHandle() const { return *m_window; };

		void onEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void Run();

	private:
		bool _CloseWindow(WindowCloseEvent& e);

	private:
		static Application* s_Instance;

		std::unique_ptr<BaseWindow> m_window;
		bool m_running = true;
		LayersStack m_layer_stack;

		//temperary test

		std::unique_ptr<VertexBuffer> vertex_buffer;
		std::unique_ptr<IndexBuffer> index_buffer;

		unsigned int m_vertex_array;

	};



	Application* createApp();
}