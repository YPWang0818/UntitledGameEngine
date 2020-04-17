#pragma once
#include "ugepch.h"
#include "Core.h"
#include "Event.h"


namespace UGE {

	class UGE_API WindowCloseEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowClose)
		_EVENT_CATEGORY_DECORATION(windowEvents)

	};


	class UGE_API WindowResizeEvent : public Event
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


	class UGE_API WindowFocusEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowFocus)
		_EVENT_CATEGORY_DECORATION(windowEvents)

	};



	class UGE_API WindowLostFocusEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowClose)
		_EVENT_CATEGORY_DECORATION(windowEvents)


	};

	class UGE_API WindowMovedEvent : public Event
	{
	public:
		_EVENT_TYPE_DECORATION(windowMoved)
		_EVENT_CATEGORY_DECORATION(windowEvents)

	};
}