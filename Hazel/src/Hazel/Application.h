#pragma once
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include <iostream>

namespace Hazel {
	class HAZEL_API Application
	{
	public:
		Application();
		~Application();

		virtual void Run();
	};
	//To be define in client
	Application* createApplication();
}
