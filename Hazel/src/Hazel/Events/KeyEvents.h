#pragma once
#include "Event.h"

namespace Hazel {

	class HAZEL_API KeyEvent
		:public Event
	{
	public:
		inline KeyCode getKeyCode() { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryKeyboard)
	protected:
		KeyEvent(KeyCode keycode)
			:m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};


	class HAZEL_API KeyPressedEvent
		:public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount) {}
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_KeyCode << "(" << m_RepeatCount << "repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	protected:

		int m_RepeatCount;

	};

	class HAZEL_API KeyReleasedEvent
		:public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode)
			:KeyEvent(keycode) {}
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)

	};


	class HAZEL_API KeyTypedEvent
		:public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode keycode)
			:KeyEvent(keycode) {}
		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)

	};

}


