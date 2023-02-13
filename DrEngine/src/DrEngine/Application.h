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
		
		virtual void Update(float deltaTime);

		virtual void Draw(float deltaTime);

		static Renderer* renderer;
		static InputManager* inputManager;
		static std::vector<ECS::CollisionComponent*> Colliders;
		static ECS::Manager* manager;
		
		/* Getters and Setters */
		Window* GetWindow() const { return window; }

		static Uint32 GetMilliseconds() { return Milliseconds; };
		static SDL_Event& GetEvent() { return event; };
		static float GetDeltaTime() { return DeltaTime; };
	private:
		static Uint32 Milliseconds;
		static SDL_Event event;
		static float DeltaTime;
		
		Window* window;

		char* AppName = "App";
	};

	// To be defined in client
	Application* CreateApplication();

}

