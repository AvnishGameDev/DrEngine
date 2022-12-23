#include "DrEngine.h"
#include "SDL.h"

class Sandbox : public DrEngine::Application
{
public:
	Sandbox() : DrEngine::Application("Sandbox", 800, 600, false)
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
		float R, G, B;
		R = 0;
		G = SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
		B = SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
		
		DE_INFO("Rendering Color frame, R: {0}, G: {1}, B: {2}, A: {3}", R, G, B, 255);
		SDL_SetRenderDrawColor(GetWindow()->GetRenderer()->GetSDLRenderer(), R, G, B, 255);
	}
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}