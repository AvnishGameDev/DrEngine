#pragma once

#include "Core.h"
#include "Window.h";

namespace DrEngine {
	namespace ECS
	{
		class Manager;
	}

	class DRENGINE_API Application
	{
	public:
		Application(char* name = "App", int width = 800, int height = 600, bool fullscreen = false);
		virtual ~Application();

		void Run();

		virtual void BeginPlay() = 0;
		
		virtual void Update();

		virtual void Draw();

		static Renderer* renderer;
		static SDL_Event event;
		static bool Keys[1024];
		
		/* Getters and Setters */
		Window* GetWindow() const { return window; }
		
		ECS::Manager* manager;
	private:
		Window* window;

		char* AppName = "App";
	};

	// To be defined in client
	Application* CreateApplication();

}

