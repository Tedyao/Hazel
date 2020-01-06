#include "hzpch.h"
#include "Application.h"


#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {
	
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_CALLBACK(onEvent));

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
			(*(--iter))->onEvent(event);
			if (event.m_Handled)
				break;
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
			for (Layer* layer : m_Layers)
			{
				layer->onUpdate();
			}
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}


}

