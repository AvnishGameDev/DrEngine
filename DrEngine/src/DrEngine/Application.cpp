#include "Application.h"

#include "ECS/ECS.h"
#include "Log.h"
#include "Renderer.h"
#include "InputManager.h"

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"

namespace DrEngine {

	Renderer* Application::renderer = nullptr;
	SDL_Event Application::event;
	InputManager* Application::inputManager;
	float Application::DeltaTime = 0.0f;
	Uint32 Application::Milliseconds = 0;

	ECS::Manager* Application::manager;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	
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

		/* TTF Init */
		if (TTF_Init() != 0)
		{
			DE_CORE_ERROR("TTF_Init Error: {0}", TTF_GetError());
		}

		/* Image Init */
		constexpr int flags = IMG_INIT_PNG | IMG_INIT_JPG;
		if (IMG_Init(flags) != flags)
		{
			DE_CORE_ERROR("IMG_Init Error: {0}", IMG_GetError());
		}
		
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
			Milliseconds = SDL_GetTicks();
			
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();

			DeltaTime = (NOW - LAST)*1000 / (float)SDL_GetPerformanceFrequency();
			
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
			
			Update(DeltaTime);
			Draw(DeltaTime);
			
			Application::inputManager->ResetMouseDelta();
		}
	}

	void Application::BeginPlay()
	{
		inputManager = new InputManager();
	}

	void Application::Update(float deltaTime)
	{
		Application::inputManager->Update();
		manager->Update(deltaTime);
	}

	void Application::Draw(float deltaTime)
	{
		SDL_RenderClear(Application::renderer->GetSDLRenderer());
		
		manager->Draw(deltaTime); // Calls Draw() on all Entities and Components
		
		SDL_SetRenderDrawColor(Application::renderer->GetSDLRenderer(), 0, 0, 0, 255);	// Let components draw color without worrying to set the colour back to default (black) before
		SDL_RenderPresent(Application::renderer->GetSDLRenderer());								// rendering next frame, if color not set to default then whole screen will be colored the RenderDrawColor.
	}

	void Application::AddCollisionComp(CollisionComponent* inComp)
	{
		manager->AddCollisionComp(inComp);
	}
}
