#pragma once
#include "Core.h"
#include "Event.h"
#include <sstream>

namespace UGE{

	class UGE_API KeyEvents : public Event
	{
	public:
		//Abstract base class for all key events.
		EVENT_CATEGORY_DECORATION(keyEvents)
		inline int getKeyCode() const { return m_keyCode; };
	protected:
		int m_keyCode;

		KeyEvents(int keyCode)
			:m_keyCode(keyCode)
		{

		};

	};

	class UGE_API KeyPressedEvent :public KeyEvents
	{
	public:
		EVENT_TYPE_DECORATION(keyPressed)

		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvents(keyCode), m_repeatCount(repeatCount)
		{

		};

		inline int getRepeatCount() const { return m_repeatCount; };
		std::string toString() const override{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

	private:
		int m_repeatCount;

	};

	class UGE_API KeyReleasedEvent : public KeyEvents
	{
	public:
		EVENT_TYPE_DECORATION(keyReleased)

		KeyReleasedEvent(int keyCode)
			:KeyEvents(keyCode)
		{

		};

		std::string toString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode;
			return ss.str();
		};

	};

}
