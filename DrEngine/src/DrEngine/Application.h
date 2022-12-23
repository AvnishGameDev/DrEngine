#pragma once

#include "Core.h"
#include "Window.h"

namespace DrEngine {

	class DRENGINE_API Application
	{
	public:
		Application(char* name);
		virtual ~Application();

		void Run();
	private:
		Window* window;

		char* AppName = "App";
	};

	// To be defined in client
	Application* CreateApplication();

}

