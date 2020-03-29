#include "UGE.h"

class Sandbox : public UGE::Application
{
public:
	Sandbox(){

	}
	~Sandbox(){

	}


};

UGE::Application* UGE::createApp()
{
	UGE_CRITICAL("fatal error!");
	//UGE::Log::getCoreLogger();
	return new Sandbox();
}