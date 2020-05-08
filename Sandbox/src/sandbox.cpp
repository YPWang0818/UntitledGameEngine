#include "UGE.h"



UGE::InputHandler& handler = UGE::InputHandler::getInputHandler();

class ExampleLayer : public UGE::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{};

	void onUpdate() override {

		UGE_TRACE("MousePos ({0}, {1})", handler.getCursorPos().x, handler.getCursorPos().y);
		if (handler.isKeyDown(UGE_KEY_F)) {
			UGE_INFO("Paying respect");
		};

	};

	void onEvent(UGE::Event& e) override {

		UGE_TRACE("Event Found {0}", e);

	

	};
};

class Sandbox : public UGE::Application
{
public:
	Sandbox() {

		PushLayer(new ExampleLayer);
		PushLayer(new UGE::ImguiLayer);

	}
	~Sandbox() {

	}


};

UGE::Application* UGE::createApp()
{

	return new Sandbox();
}