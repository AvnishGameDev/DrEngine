#include "Application.h"

#include "ECS/ECS.h"
#include "Log.h"
#include "SDL.h"
#include "Renderer.h"

namespace DrEngine {

	Renderer* Application::renderer = nullptr;
	
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
			Update();
			Draw();
		}
	}
	
	void Application::Update()
	{
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
