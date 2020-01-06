#pragma once
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "Hazel/Log.h"
#include <gl/GL.h>


namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		~Application();

		virtual void Run();
		void onEvent(Event& event);
		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_Layers;
		bool m_Running = true;

		bool windowClose(WindowCloseEvent& event);
	};


	//To be define in client
	Application* createApplication();
}
