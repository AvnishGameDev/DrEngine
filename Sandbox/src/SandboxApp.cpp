#include "DrEngine.h"
#include "SDL.h"
#include "Components/CubeController.h"
#include "Components/ScaleBlendComp.h"
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
		e1->AddComponent<RectComp>(0, 255, 0);
		e1->AddComponent<CubeController>();
		Entities.push_back(e1);
		
		
		auto e2 = manager->AddEntity(PlayerComp);
		e2->AddComponent<TransformComponent>();
		e2->GetComponentByClass<TransformComponent>()->Location = Vector2D(150, 100);
		e2->GetComponentByClass<TransformComponent>()->Scale = Vector2D(100, 100);
		e2->AddComponent<RectComp>(0, 0, 255);
		Entities.push_back(e2);
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