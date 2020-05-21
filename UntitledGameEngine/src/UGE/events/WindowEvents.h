#pragma once
#include "ugepch.h"
#include "Core.h"
#include "Event.h"


namespace UGE {

	class  WindowCloseEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowClose)
		_EVENT_CATEGORY_DECORATION(windowEvents)

	};


	class  WindowResizeEvent : public Event
	{
	public:

		_EVENT_TYPE_DECORATION(windowResize)
		_EVENT_CATEGORY_DECORATION(windowEvents)

		WindowResizeEvent(unsigned int width, unsigned int hight)
			:m_width(width), m_hight(hight)
		{

		};
		
		inline unsigned int getWidth() const{ return m_width; };
		inline unsigned int getHight() const{ return m_hight; };

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowResize Event: Width " << m_width << " Hight " << m_hight;

			return ss.str();
		}


	private:
		unsigned int m_width;
		unsigned int m_hight;
	};


	class  WindowFocusEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowFocus)
		_EVENT_CATEGORY_DECORATION(windowEvents)

	};



	class  WindowLostFocusEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowClose)
		_EVENT_CATEGORY_DECORATION(windowEvents)


	};

	class  WindowMovedEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowMoved)
		_EVENT_CATEGORY_DECORATION(windowEvents)

	};
}