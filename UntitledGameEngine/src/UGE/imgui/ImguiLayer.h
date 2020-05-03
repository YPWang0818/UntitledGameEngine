#pragma once
#include "ugepch.h"
#include "UGE/Layer.h"
#include "events/evt_Includes.h"

namespace UGE{
	
	class UGE_API ImguiLayer : public Layer
	{
	public:

		ImguiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent(Event & e);

	private:
		float m_time;

		bool _KeyCallBack(Event& e);
		bool _MouseButtonCallBack(Event& e);
		bool _CursorPosCallBack(Event& e);
		bool _ScrollCallBack(Event& e);
		//bool _CharCallBack(Event& e);
	};

};
