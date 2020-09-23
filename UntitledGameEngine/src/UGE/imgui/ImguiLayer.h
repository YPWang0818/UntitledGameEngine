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
	
	};

};
