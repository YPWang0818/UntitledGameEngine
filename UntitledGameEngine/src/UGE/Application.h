#pragma once
#include "Core.h"

namespace UGE {
	class UGE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application* createApp();
}