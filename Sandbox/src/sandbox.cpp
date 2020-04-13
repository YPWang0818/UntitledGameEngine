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

	return new Sandbox();
}