#pragma once
#include "Event.h"


namespace Hazel {

	class HAZEL_API WindowResizeEvent
		:public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height)
		{

		}
		~WindowResizeEvent()
		{

		}

		inline float getWidth() { return m_Width; }
		inline float getHeight() { return m_Height; }


		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)



	private:
		unsigned int m_Width, m_Height;
	};


	class HAZEL_API WindowCloseEvent
		:public Event
	{
	public:

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();

		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};


	class HAZEL_API AppTickEvent
		:public Event
	{
	public:

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "AppTickEvent";
			return ss.str();

		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};

	class HAZEL_API AppUpdateEvent
		:public Event
	{
	public:

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "AppUpdateEvent";
			return ss.str();

		}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};


	class HAZEL_API AppRenderEvent
		:public Event
	{
	public:

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "AppTickEvent";
			return ss.str();

		}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryApplication)
	};
	
}




