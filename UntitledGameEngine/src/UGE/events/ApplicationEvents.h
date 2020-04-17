#pragma once
#include "ugepch.h"
#include "Core.h"
#include "Event.h"


namespace UGE {

	class UGE_API AppTickEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(appTick)
		_EVENT_CATEGORY_DECORATION(appEvents)
	};

	class UGE_API AppUpdateEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(appUpdate)
		_EVENT_CATEGORY_DECORATION(appEvents)
	};


	class UGE_API AppRenderEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(appRender)
		_EVENT_CATEGORY_DECORATION(appEvents)
	};


}