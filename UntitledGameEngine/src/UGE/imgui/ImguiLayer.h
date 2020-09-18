#pragma once
#include "core/Layer.h"
#include "events/uge_events.h"

namespace UGE{
	
	class  ImguiLayer : public Layer
	{
	public:

		ImguiLayer();

		void onAttach() override;
		void onDetach() override;
		void onUpdate(TimeStep ts) override;
		void onEvent(Event & e) override;

		static void Begin();
		static void End();
	

	private:
		bool _KeyPressedCallBack(KeyPressedEvent& e);
		bool _KeyReleasedCallBack(KeyReleasedEvent& e);
		bool _MousePressedCallBack(MousePressedEvent& e);
		bool _MouseReleasedCallBack(MouseReleasedEvent& e);
		bool _CursorPosCallBack(MouseMovedEvent& e);
		bool _ScrollCallBack(MouseScrolledEvent& e);
		bool _CharCallBack(KeyTypedEvent& e);
		bool _WindowResizeCallBack(WindowResizeEvent& e);
		bool _WindowMovedCallBack(WindowMovedEvent& e);
		//bool _WindowFocusedCallBack(WindowFocusEvent& e);
		//bool _WindowUnFocusedCallBack(WindowLostFocusEvent& e);
		
	};

};
