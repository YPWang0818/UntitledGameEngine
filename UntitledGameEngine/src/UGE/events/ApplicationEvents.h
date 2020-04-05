#pragma once
#include "ugepch.h"
#include "Core.h"
#include "Event.h"


namespace UGE {

	class UGE_API AppTickEvent : public Event
	{
	public:
		EVENT_TYPE_DECORATION(appTick)
		EVENT_CATEGORY_DECORATION(appEvents)
	};

	class UGE_API AppUpdateEvent : public Event
	{
	public:
		EVENT_TYPE_DECORATION(appUpdate)
		EVENT_CATEGORY_DECORATION(appEvents)
	};


	class UGE_API AppRenderEvent : public Event
	{
	public:
		EVENT_TYPE_DECORATION(appRender)
		EVENT_CATEGORY_DECORATION(appEvents)
	};


}