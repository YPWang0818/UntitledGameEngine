#pragma once
#include "core/Layer.h"
#include "events/uge_events.h"

namespace UGE{
	
	class  ImguiLayer : public Layer
	{
	public:

		ImguiLayer(const std::string& debug_name);
		~ImguiLayer();

		void onEvent(Event & e) override;

		static void BeginUI();
		static void EndUI();
	
	};

};
