#include "DrEngine.h"
#include "SDL.h"
#include "Components/BallComponent.h"
#include "Components/CubeController.h"
#include "Components/PaddleController.h"
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
		Application::BeginPlay();

		auto p1 = manager->AddEntity("paddle1");
		p1->AddComponent<TransformComponent>();
		p1->GetComponentByClass<TransformComponent>()->Location = Vector2D(20, 200);
		p1->GetComponentByClass<TransformComponent>()->Scale = Vector2D(10, 100);
		p1->AddComponent<RectComp>();
		p1->AddComponent<CollisionComponent>();
		p1->AddComponent<PaddleController>();
		paddles.push_back(p1);

		auto p2 = manager->AddEntity("paddle2");
		p2->AddComponent<TransformComponent>();
		p2->GetComponentByClass<TransformComponent>()->Location = Vector2D(760, 200);
		p2->GetComponentByClass<TransformComponent>()->Scale = Vector2D(10, 100);
		p2->AddComponent<RectComp>();
		p2->AddComponent<CollisionComponent>();
		p2->AddComponent<PaddleController>();
		paddles.push_back(p2);

		Ball = manager->AddEntity("Ball");
		Ball->AddComponent<TransformComponent>();
		Ball->GetComponentByClass<TransformComponent>()->Location = Vector2D(280, 280);
		Ball->GetComponentByClass<TransformComponent>()->Scale = Vector2D(12, 12);
		Ball->GetComponentByClass<TransformComponent>()->Velocity = Vector2D(0.2f, -0.1f);
		Ball->AddComponent<RectComp>();
		Ball->AddComponent<CollisionComponent>();
		Ball->AddComponent<BallComponent>(paddles);
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

	std::vector<Entity*> paddles;
	Entity* Ball;
	
	int i{0};
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}