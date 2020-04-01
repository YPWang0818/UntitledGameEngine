#pragma once

#include "Core.h"
#include "Event.h"
#include <sstream>

namespace UGE {

	class UGE_API MouseMovedEvent : public Event 
	{
	public:

		EVENT_TYPE_DECORATION(mouseMoved)
		EVENT_CATEGORY_DECORATION(mouseEvents)

		MouseMovedEvent(int xPos, int yPos)
			:m_xPos(xPos), m_yPos(yPos)
		{};

		inline int getXPos() const { return m_xPos; };
		inline int getYPos() const { return m_yPos; };

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: ( " << m_xPos << " , " << m_yPos <<  " )";

			return ss.str();
		}
	private:
		int m_xPos;
		int m_yPos;
	};

	class UGE_API MouseScrolledEvent : public Event {

	public:
		EVENT_TYPE_DECORATION(mouseScrolled)
		EVENT_CATEGORY_DECORATION(mouseEvents)

		MouseMovedEvent(int xOffset, int yOffset)
			:m_xOffset(xOffset), m_yOffset(yOffset)
		{}

	private:
		int m_xOffset;
		int m_yOffset;

	};



}