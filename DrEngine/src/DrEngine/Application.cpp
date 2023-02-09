#include "Application.h"

#include "ECS/ECS.h"
#include "Log.h"
#include "SDL.h"
#include "Renderer.h"

namespace DrEngine {

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
		Renderer* ren = new Renderer();
		if (!ren->Initialize(window))
		{
			DE_CORE_ERROR("Renderer failed to initialize");
		}

		/* Attaching Renderer to Window */
		window->SetRenderer(ren);

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
			window->UpdateRender();
		}
	}
	
	void Application::Update()
	{
		manager->Update();
	}

	void Application::Draw()
	{
		manager->Draw();
	}
}
