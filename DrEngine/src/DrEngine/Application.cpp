#include "Application.h"

#include "Log.h"
#include "SDL.h"

namespace DrEngine {

	Application::Application(char* name)
	{
		AppName = name;
		
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			DE_CORE_ERROR("SDL_Init Error: {0}", SDL_GetError());
		}

		window = new Window();
		if (!window->Initialize(AppName, 800, 600, false))
		{
			DE_CORE_ERROR("Window failed to initialize");
		}
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (true);
	}
}