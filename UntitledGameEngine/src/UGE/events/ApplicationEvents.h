#pragma once
#include "ugepch.h"
#include "core/Core.h"
#include "Event.h"


namespace UGE {

	class  AppTickEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(appTick)
		_EVENT_CATEGORY_DECORATION(appEvents)
	};

	class  AppUpdateEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(appUpdate)
		_EVENT_CATEGORY_DECORATION(appEvents)
	};


	class  AppRenderEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(appRender)
		_EVENT_CATEGORY_DECORATION(appEvents)
	};


}