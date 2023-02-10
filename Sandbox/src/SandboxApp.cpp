#include "DrEngine.h"
#include "SDL.h"
#include "Components/TrigMovement.h"

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
		auto e1 = manager->AddEntity();
		e1->AddComponent<TransformComponent>();
		e1->GetComponentByClass<TransformComponent>()->Location = Vector2D(100, 100);
		e1->GetComponentByClass<TransformComponent>()->Scale = Vector2D(100, 100);
		e1->AddComponent<RectComp>();
		e1->AddComponent<TrigMovement>(Sin, true);
		e1->AddComponent<CircleComp>();
		Entities.push_back(e1);

		auto e2 = manager->AddEntity();
		e2->AddComponent<TransformComponent>();
		e2->GetComponentByClass<TransformComponent>()->Location = Vector2D(100, 100);
		e2->GetComponentByClass<TransformComponent>()->Scale = Vector2D(100, 100);
		e2->AddComponent<RectComp>();
		e2->AddComponent<TrigMovement>(Cos, false);
		Entities.push_back(e2);

		auto e3 = manager->AddEntity();
		e3->AddComponent<TransformComponent>();
		e3->GetComponentByClass<TransformComponent>()->Location = Vector2D(100, 100);
		e3->GetComponentByClass<TransformComponent>()->Scale = Vector2D(100, 100);
		e3->AddComponent<RectComp>();
		e3->AddComponent<TrigMovement>(Tan, false);
		Entities.push_back(e3);
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

	std::vector<Entity*> Entities;
	
	int i{0};
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}