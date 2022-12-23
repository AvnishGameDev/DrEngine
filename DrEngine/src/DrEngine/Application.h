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

		virtual void BeginPlay() = 0;
		
		virtual void Update() = 0;
		
		/* Getters and Setters */
		Window* GetWindow() const { return window; }
	private:
		Window* window;

		char* AppName = "App";
	};

	// To be defined in client
	Application* CreateApplication();

}

