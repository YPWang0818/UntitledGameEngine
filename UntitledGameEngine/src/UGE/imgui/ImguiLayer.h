#pragma once
#include "ugepch.h"
#include "UGE/Layer.h"

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
	};

};
