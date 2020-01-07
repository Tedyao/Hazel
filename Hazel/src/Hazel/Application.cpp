#include "hzpch.h"
#include "Application.h"


#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {
	//Application* m_Instance;

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application has already been instanced!");
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_CALLBACK(onEvent));
		s_Instance = this;

	}

	Application::~Application()
	{
	
	}


	void Application::onEvent(Event& event)
	{

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(windowClose));
		for (auto iter = m_Layers.end(); iter != m_Layers.begin(); )
		{
			if (event.m_Handled)
				break;
			(*(--iter))->onEvent(event);
			if (Input::isMouseButtonPressed(0))
				HZ_CORE_WARN("Left Mouse Button is being pressed!");
		}

		//HZ_CORE_TRACE("[Event]: {0}", event.toString());
	}

	void Application::pushLayer(Layer* layer)
	{
		m_Layers.pushLayer(layer);
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_Layers.pushOverlay(layer);
	}

	bool Application::windowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}


	void Application::Run()
	{
		
		while (m_Running)
		{
			glClearColor(1.0, 0.0, 1.0, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_Layers)
			{
				layer->onUpdate();
			}
			
			m_Window->OnUpdate();
		}
	}


}

