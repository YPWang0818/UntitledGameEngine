#pragma once
#include"Application.h"

extern UGE::Application* UGE::createApp();


int main(int argc, char** argv) {

	auto app = UGE::createApp();
	app->Run();
	delete app;


}