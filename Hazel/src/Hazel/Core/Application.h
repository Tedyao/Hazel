#pragma once
#include "Core.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Core/Window.h"
#include "LayerStack.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Core/Input.h"
#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/Renderer2D.h"
#include "Hazel/Core/TimeStep.h"

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
		inline Window& getWindow() { return *m_Window; }
		inline static Application& getInstance() { return *s_Instance; }
		inline void setRunning(bool running) { m_Running = running; }

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;
		bool windowClose(WindowCloseEvent& event);
		bool windowResize(WindowResizeEvent& event);

	private:
		float m_LastFrameTime = 0.0f;
	protected:
		ImGuiLayer* imguiLayer;
		bool m_Running = true;
		LayerStack m_Layers;
	};
	//To be define in client
	Application* createApplication();
}
