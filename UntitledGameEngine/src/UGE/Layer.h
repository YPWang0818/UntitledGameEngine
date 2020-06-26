#pragma once
#include "ugepch.h"
#include "events/uge_events.h"
#include "UGE/TimeStep.h"

namespace UGE {
	class  Layer
	{
	public:
		Layer(const std::string& debug_name);
		virtual ~Layer() = default;
		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate(TimeStep ts) {};
		virtual void onEvent(Event& e) {};

		virtual inline std::string getName() const { return m_debug_name; };
	private:
		std::string m_debug_name;
	};
}
