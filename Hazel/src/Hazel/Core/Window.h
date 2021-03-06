#pragma once
#include "hzpch.h"
#include "Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel{

	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hazel Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{

		}
	};


	// Interface representation a desktop system based window
	class HAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window();

		virtual void OnUpdate() = 0;
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		//Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSysn() const = 0;
		virtual void* getNativeWindow() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());

	};
}