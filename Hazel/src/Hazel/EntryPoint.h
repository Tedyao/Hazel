#pragma once

#ifdef HZ_PLATFORM_WINDOWS
extern Hazel::Application* Hazel::createApplication();
int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_ERROR("hello");

	Hazel::MouseButtonPressedEvent e(1);
	HZ_CORE_ERROR(e.toString());
	auto app = Hazel::createApplication();
	app->Run();
	delete app;

}

#endif