#include "DrEngine.h"
#include "SDL.h"

class Sandbox : public DrEngine::Application
{
public:
	Sandbox() : DrEngine::Application("Sandbox")
	{
	}

	~Sandbox()
	{
	}

	virtual void BeginPlay() override
	{
		
	}

	virtual void Update() override
	{
		DE_INFO("Rendering Color frame, R: {0}, G: {1}, B: {2}, A: {3}", 0, 0.66 * 255, 255, 255);
		SDL_RenderClear(GetWindow()->GetRenderer()->GetSDLRenderer());
		SDL_SetRenderDrawColor(GetWindow()->GetRenderer()->GetSDLRenderer(), 0, 0.66 * 255, 255, 255);
		SDL_RenderPresent(GetWindow()->GetRenderer()->GetSDLRenderer());
	}
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}