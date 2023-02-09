#include "DrEngine.h"
#include "SDL.h"
#include "Components/SineMovement.h"
#include "Components/TestComp.h"

using namespace DrEngine;
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
		auto t = cube->AddComponent<TransformComponent>();
		cube->AddComponent<RectComp>(t);
		t->Location = Vector2D(100, 100);
		t->Scale = Vector2D(100, 100);
		cube->AddComponent<SineMovement>(t);
	}

	virtual void Update() override
	{
		Application::Update();
		
		i++;
	}
	Entity* cube;

	int i{0};
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}