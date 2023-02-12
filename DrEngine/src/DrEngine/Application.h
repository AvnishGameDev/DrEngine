#pragma once

#include <map>
#include <vector>

#include "Core.h"
#include "Window.h"

namespace DrEngine {

	class InputManager;
	
	namespace ECS
	{
		class Manager;
		class CollisionComponent;
	}

	class DRENGINE_API Application
	{
	public:
		Application(char* name = "App", int width = 800, int height = 600, bool fullscreen = false);
		virtual ~Application();

		void Run();

		virtual void BeginPlay();
		
		virtual void Update();

		virtual void Draw();

		static Renderer* renderer;
		static SDL_Event event;
		static InputManager* inputManager;
		static std::vector<ECS::CollisionComponent*> Colliders;
		static Uint32 deltaTime;
		
		/* Getters and Setters */
		Window* GetWindow() const { return window; }
		
		static ECS::Manager* manager;
	private:
		Window* window;

		char* AppName = "App";
	};

	// To be defined in client
	Application* CreateApplication();

}

