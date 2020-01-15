#pragma once

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::createApplication();
int main(int argc, char** argv)
{

	
	Hazel::Log::Init();
	auto app = Hazel::createApplication();
	app->Run();
	delete app;

}

#endif