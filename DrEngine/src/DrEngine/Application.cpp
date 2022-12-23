#include "Application.h"

#include "Log.h"
#include "SDL.h"
#include "Renderer.h"

namespace DrEngine {

	Application::Application(char* name)
	{
		AppName = name;

		/* SDL Init */
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			DE_CORE_ERROR("SDL_Init Error: {0}", SDL_GetError());
		}

		/* Creating Window */
		window = new Window();
		if (!window->Initialize(AppName, 800, 600, false))
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
		}
	}
}