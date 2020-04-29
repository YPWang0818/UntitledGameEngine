#include "Sandbox.h"
#include <UGE.h>

class ExampleLayer: public UGE::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{};

	void onUpdate() override {

	//UGE_TRACE("Example Layer Updated");
	};

	void onEvent(UGE::Event& e) override {
		
		UGE_TRACE("Event Found {0}", e);
		
	};
};

class Sandbox : public UGE::Application
{
public:
	Sandbox(){

		PushLayer(new ExampleLayer);

	}
	~Sandbox(){

	}


};

UGE::Application* UGE::createApp()
{

	return new Sandbox();
}