#pragma once
#include "Event.h"

namespace Hazel {


	class HAZEL_API MouseMovedEvent
		:public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y) {}

		inline float getX() const { return m_MouseX; }
		inline float getY() const { return m_MouseY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MousedMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput || EventCategory::EventCategoryMouse)
	private:
		float m_MouseX, m_MouseY;
	};

	class HAZEL_API MouseScrolledEvent
		:public Event
	{
	public:
		MouseScrolledEvent(float x, float y)
			:m_OffsetX(x), m_OffsetY(y) {}

		inline float getXOffset() const { return m_OffsetX; }
		inline float getYOffset() const { return m_OffsetY; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MousedScorlledEvent: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput || EventCategory::EventCategoryMouse)
	private:
		float m_OffsetX, m_OffsetY;
	};


	class HAZEL_API MouseButtonEvent
		:public Event
	{
	public:

		inline MouseCode getButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput || EventCategory::EventCategoryMouse)
	protected:
		MouseButtonEvent(MouseCode button)
			:m_Button(button) {}
		MouseCode m_Button;
	};


	class HAZEL_API MouseButtonPressedEvent
		:public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			:MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class HAZEL_API MouseButtonReleasedEvent
		:public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			:MouseButtonEvent(button) {}

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)

	};
}

