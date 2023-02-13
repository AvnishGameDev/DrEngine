#pragma warning (push)
#pragma warning (disable: 4251)
#include "DrEngine.h"
#pragma warning (pop)

#include "SDL.h"
#include "Components/BallComponent.h"
#include "Components/CubeController.h"
#include "Components/PaddleController.h"
#include "Components/ScaleBlendComp.h"
#include "Components/TrigMovement.h"

#include "SDL_ttf.h"
#include "Components/FpsComp.h"

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
		p1->AddComponent<RectComp>(0, 255, 0);
		p1->AddComponent<CollisionComponent>();
		p1->AddComponent<PaddleController>();
		paddles.push_back(p1);

		auto p2 = manager->AddEntity("paddle2");
		p2->AddComponent<TransformComponent>();
		p2->GetComponentByClass<TransformComponent>()->Location = Vector2D(760, 200);
		p2->GetComponentByClass<TransformComponent>()->Scale = Vector2D(10, 100);
		p2->AddComponent<RectComp>(0, 0, 255);
		p2->AddComponent<CollisionComponent>();
		p2->AddComponent<PaddleController>();
		paddles.push_back(p2);

		Ball = manager->AddEntity("Ball");
		Ball->AddComponent<TransformComponent>();
		Ball->GetComponentByClass<TransformComponent>()->Location = Vector2D(280, 280);
		Ball->GetComponentByClass<TransformComponent>()->Scale = Vector2D(36, 36);
		Ball->GetComponentByClass<TransformComponent>()->Velocity = Vector2D(0.28f, -0.28f);
		Ball->AddComponent<RectComp>(0, 0, 0)->SetVisibility(false);
		Ball->AddComponent<CollisionComponent>();
		Ball->AddComponent<BallComponent>(paddles);
		Ball->AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 28, "Score: 0");
		Ball->AddComponent<SpriteComponent>("Assets/Images/ball.png");

		FpsCounter = manager->AddEntity("FpsCounter");
		FpsCounter->AddComponent<FpsComp>();
		const auto fpsText = FpsCounter->AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 18, "FPS: 30");
		fpsText->SetLocation(Vector2D(720, 10));
		fpsText->SetColor({255, 255, 255, 255});

		Desc = manager->AddEntity("Desc");
		const auto descText = Desc->AddComponent<TextComp>("Assets/Fonts/Sans.ttf", 14, "Made using DrEngine. Made by AvnishGameDev.");
		descText->SetLocation(Vector2D(460, 580));
		descText->SetPulse(true);

		bg = manager->AddEntity("bg");
		bg->SetBatch(Tile);
		bg->AddComponent<TransformComponent>()->Scale = Vector2D(800, 600);
		bg->AddComponent<RectComp>();
		bg->AddComponent<SpriteComponent>("Assets/Images/bg-updated.jpg");
		
	}

	virtual void Update(float deltaTime) override
	{
		Application::Update(deltaTime);

		int ballScore =  Ball->GetComponentByClass<BallComponent>()->GetScore();
		if (currentScore != ballScore)
		{
			currentScore = ballScore;
			std::string text = "Score: " + std::to_string(currentScore);
			Ball->GetComponentByClass<TextComp>()->SetText(text);
		}

		float fps = FpsCounter->GetComponentByClass<FpsComp>()->GetFPS();
		std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
		FpsCounter->GetComponentByClass<TextComp>()->SetText(fpsText);
		
		i++;
	}

	virtual void Draw(float deltaTime) override
	{
		Application::Draw(deltaTime);
		
	}

	std::vector<Entity*> paddles;
	Entity* Ball;
	Entity* FpsCounter;
	Entity* Desc;
	Entity* bg;

	int currentScore{0};
	
	int i{0};
};

DrEngine::Application* DrEngine::CreateApplication()
{
	return new Sandbox();
}