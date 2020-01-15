#pragma once
#include "Core.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Core/TimeStep.h"

namespace Hazel {
	class HAZEL_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void onAttach() {};
		virtual void onDetach() {};
		virtual void onUpdate(TimeStep time) {};
		virtual void OnImGuiRender() {};
		virtual void onEvent(Event& event) {};
		inline std::string getName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};

}