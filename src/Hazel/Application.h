#pragma once
#include "Core.h"

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
