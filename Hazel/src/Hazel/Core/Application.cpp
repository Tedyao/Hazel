#include "hzpch.h"
#include "Application.h"
#include "GLFW/glfw3.h"

#define BIND_EVENT_CALLBACK(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Hazel {
	//Application* m_Instance;

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application has already been instanced!");
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->setEventCallback(BIND_EVENT_CALLBACK(onEvent));
		Renderer::Init();
		s_Instance = this;
		imguiLayer = new ImGuiLayer();
		pushOverlay(imguiLayer);
	}

	Application::~Application()
	{

	}


	void Application::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_CALLBACK(windowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_CALLBACK(windowResize));

		for (auto iter = m_Layers.end(); iter != m_Layers.begin(); )
		{
			if (event.m_Handled)
				break;
			(*(--iter))->onEvent(event);
			
		}
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


	bool Application::windowResize(WindowResizeEvent& event)
	{
		Hazel::Renderer::setViewPort(event.getWidth(), event.getHeight());
		return false;
	}

	void Application::Run()
	{
		
		while (m_Running)
		{
			float time = glfwGetTime();
			TimeStep timeStep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			//HZ_CORE_TRACE("Time to render last frame: {0}s ({1}ms)", timeStep.getSeconds(), timeStep.getMillSeconds());
			
			for (Layer* layer : m_Layers)
			{
				layer->onUpdate(timeStep);
			}

			imguiLayer->Begin();
			for (Layer* layer : m_Layers)
			{
				layer->OnImGuiRender();
			}
			imguiLayer->End();

			getWindow().OnUpdate();
		}
	}


}

