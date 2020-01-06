#include "Hazel.h"

class ExampleLayer
	:public Hazel::Layer
{
public:
	ExampleLayer(const std::string& name = "Example Layer")
		:Layer(name)
	{

	}
	~ExampleLayer()
	{

	}
	void onEvent(Hazel::Event& event) override
	{
		HZ_INFO(event.toString());
	}

	void onUpdate() override
	{
		HZ_INFO("{0} layer updated.", getName());
	}
};


class SandBox
	:public Hazel::Application
{
public:
	SandBox()
	{
		pushLayer(new ExampleLayer("layer1"));
		pushLayer(new ExampleLayer("layer2"));
		pushOverlay(new ExampleLayer("Overlay1"));
		
	}
	~SandBox()
	{

	}


};

Hazel::Application* Hazel::createApplication()
{
	return new SandBox();
	
}






