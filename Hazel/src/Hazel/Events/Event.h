#pragma once
#include "Hazel/Core.h"
#include <iostream>
#define MouseCode int
#define KeyCode int


namespace Hazel {
	// Event in Hazel are currently blocking, meaning an event occurs it
	// immediately get dispatched and must be dealt with right then an there.
	// For future, a better strategy might be to buffer events in an event bus
	// and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseBotton = BIT(4),
	};




#define EVENT_CLASS_TYPE(type) static EventType getStaticType() {return EventType::type;}\
										virtual EventType getEventType() const override {return getStaticType();}\
										virtual const char* getName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override {return category;} 
	class HAZEL_API Event
	{
	public:
		bool m_Handled = false;

		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); };

		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}

		

	};

	std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	

}