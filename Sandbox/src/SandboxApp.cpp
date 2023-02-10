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
		cube1 = manager->AddEntity("cube1");
		auto t1 = cube1->AddComponent<TransformComponent>();
		t1->Location = Vector2D(100, 100);
		t1->Scale = Vector2D(100, 100);
		cube1->AddComponent<RectComp>();

		cube2 = manager->AddEntity("cube2");
		auto t2 = cube2->AddComponent<TransformComponent>();
		t2->Location = Vector2D(240, 100);
		t2->Scale = Vector2D(100, 100);
		cube2->AddComponent<RectComp>();
		cube2->AddComponent<SineMovement>();
	}

	virtual void Update() override
	{
		Application::Update();
		
		i++;
	}

	virtual void Draw() override
	{
		Application::Draw();
		
	}

	Entity* cube1;
	Entity* cube2;
	
	int i{0};
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}