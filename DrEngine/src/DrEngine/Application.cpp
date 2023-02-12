#include "Application.h"

#include "ECS/ECS.h"
#include "Log.h"
#include "SDL.h"
#include "Renderer.h"
#include "InputManager.h"

namespace DrEngine {

	Renderer* Application::renderer = nullptr;
	SDL_Event Application::event;
	InputManager* Application::inputManager;
	std::vector<ECS::CollisionComponent*> Application::Colliders;
	Uint32 Application::deltaTime = 0.0f;

	Uint32 lastTickTime = 0;
	
	Application::Application(char* name, int width, int height, bool fullscreen)
	{
		AppName = name;

		/* SDL Init */
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			DE_CORE_ERROR("SDL_Init Error: {0}", SDL_GetError());
		}

		/* Creating Window */
		window = new Window();
		if (!window->Initialize(AppName, width, height, fullscreen))
		{
			DE_CORE_ERROR("Window failed to initialize");
		}

		/* Creating Renderer */
		renderer = new Renderer();
		if (!renderer->Initialize(window))
		{
			DE_CORE_ERROR("Renderer failed to initialize");
		}

		/* Attaching Renderer to Window */
		window->SetRenderer(renderer);

		/* Init Manager */
		manager = new ECS::Manager();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		BeginPlay();
		while (true)
		{
			uint32_t tick_time = SDL_GetTicks();
			deltaTime = tick_time - lastTickTime;
			lastTickTime = tick_time;
			
			SDL_PumpEvents();
			while (SDL_PollEvent(&Application::event))
			{
				Application::inputManager->PollEvent();
				if ((event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) || event.type == SDL_QUIT)
				{
					SDL_Quit();
					return;
				}
			}
			
			Update();
			Draw();
			
			Application::inputManager->ResetMouseDelta();
		}
	}

	void Application::BeginPlay()
	{
		inputManager = new InputManager();
	}

	void Application::Update()
	{
		Application::inputManager->Update();
		manager->Update();
	}

	void Application::Draw()
	{
		SDL_RenderClear(Application::renderer->GetSDLRenderer());
		
		manager->Draw(); // Calls Draw() on all Entities and Components
		
		SDL_SetRenderDrawColor(Application::renderer->GetSDLRenderer(), 0, 0, 0, 255);	// Let components draw color without worrying to set the colour back to default (black) before
		SDL_RenderPresent(Application::renderer->GetSDLRenderer());								// rendering next frame, if color not set to default then whole screen will be colored the RenderDrawColor.
	}
}
