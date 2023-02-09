#include "DrEngine.h"
#include "SDL.h"
#include "Components/TestComp.h"

using namespace DrEngine::ECS;

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
		cube = manager->AddEntity();
		//cube->AddComponent<TransformComponent>();
		//cube->AddComponent<RectComp>();
	}

	virtual void Update() override
	{
		Application::Update();
		
		float R, G, B;
		R = 0;
		G = SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
		B = SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
		
		//DE_INFO("Rendering Color frame, R: {0}, G: {1}, B: {2}, A: {3}", R, G, B, 255);
		SDL_SetRenderDrawColor(GetWindow()->GetRenderer()->GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(GetWindow()->GetRenderer()->GetSDLRenderer());

		const int posX = 700.0f  / 2.0f + SDL_sinf(SDL_GetTicks() / 1000.0f * 3.18378f) * (700.0f / 2.0f);
		const int posY = 500.0f / 2.0f + SDL_cosf(SDL_GetTicks() / 1000.0f) * (500.0f / 2.0f);
		
		SDL_Rect rect = {posX, posY, 100, 100};
		
		SDL_SetRenderDrawColor(GetWindow()->GetRenderer()->GetSDLRenderer(), R, G, B, 255);
		SDL_RenderFillRect(GetWindow()->GetRenderer()->GetSDLRenderer(), &rect);
		SDL_RenderPresent(GetWindow()->GetRenderer()->GetSDLRenderer());
		
		i++;
	}
	Entity* cube;

	int i{0};
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}