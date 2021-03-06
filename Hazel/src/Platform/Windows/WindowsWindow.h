#pragma once

#include "Hazel/Core/Window.h"
#include "Hazel/Core/Core.h"
#include <GLFW/glfw3.h>
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Core/Log.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Hazel/Renderer/GraphicsContext.h"

namespace Hazel {
	class WindowsWindow
		:public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		inline unsigned int getWidth() const override  { return m_Data.Width; }
		inline unsigned int getHeight() const override  { return m_Data.Height; }

		// Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSysn() const override;

		virtual void* getNativeWindow() const override;

	private:
		virtual void Init(const WindowProps props);
		virtual void shutDown();

	private:
		//static bool isGLFWInitilized;
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			bool vSync;
			EventCallbackFn EventCallback;

		};
		WindowData m_Data;
		GraphicsContext* m_Context;
	};
}
