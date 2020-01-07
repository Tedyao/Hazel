#pragma once
#include "Hazel/Layer.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {
	class HAZEL_API ImGuiLayer
		:public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(Event& event) override;

	private:
		bool onMouseMovedEvent(MouseMovedEvent& event);
		bool onMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool onMouseScrolledEvent(MouseScrolledEvent& event);
		bool onKeyPressedEvent(KeyPressedEvent& event);
		bool onKeyReleasedEvent(KeyReleasedEvent& event);
		bool onKeyTypedEvent(KeyTypedEvent& event);
		bool onWindowResizedEvent(WindowResizeEvent& event);




	private:
		float m_Time = 0.0f;
	};
}