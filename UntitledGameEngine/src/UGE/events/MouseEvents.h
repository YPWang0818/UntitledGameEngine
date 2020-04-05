#pragma once
#include "ugepch.h"
#include "Core.h"
#include "Event.h"


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

		MouseScrolledEvent(int xOffset, int yOffset)
			:m_xOffset(xOffset), m_yOffset(yOffset)
		{};

		inline int getxOffset() const { return m_xOffset; };
		inline int getyOffset() const { return m_yOffset; };

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: ( " << m_xOffset << " , " << m_yOffset << " )";

			return ss.str();
		};


	private:
		int m_xOffset;
		int m_yOffset;

	};

	class UGE_API MouseButtonEvents : public Event
	{
		// Abstract class for mouse button events.
	public:
		EVENT_CATEGORY_DECORATION(mouseEvents)
		inline int getMosueButton() const { return m_button; };
	
	protected:
		MouseButtonEvents(int button)
			: m_button(button)
		{};

		int m_button;

	};


	class UGE_API MousePressedEvent : public MouseButtonEvents
	{
		// Abstract class for mouse button events.
	public:
		EVENT_TYPE_DECORATION(mousePressed)
		MousePressedEvent(int button)
			: MouseButtonEvents(button)
		{};

		std::string toString() const override {
			std::stringstream ss;
			ss << "MousePressedEvent:" << m_button;

			return ss.str();
		};


	};

	class UGE_API MouseReleasedEvent : public MouseButtonEvents
	{
		// Abstract class for mouse button events.
	public:
		EVENT_TYPE_DECORATION(mouseReleased)
			MouseReleasedEvent(int button)
			: MouseButtonEvents(button)
		{};

		std::string toString() const override {
			std::stringstream ss;
			ss << "MouseReleasedEvent:" << m_button;

			return ss.str();
		};


	};
}
