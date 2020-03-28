#pragma once
#include"Application.h"
//#include "Log.h"

extern UGE::Application* UGE::createApp();


int main(int argc, char** argv) {

	UGE::Log::Init();
	UGE_CORE_WARN("Warning!!");
	UGE_TRACE("Unimportant stuff");

	auto app = UGE::createApp();
	app->Run();
	delete app;


}