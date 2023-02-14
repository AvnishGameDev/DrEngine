#pragma once

#include "DrEngine.h"

using namespace DrEngine;

class Paddle : public Entity
{
public:
    Paddle(const Vector2D& inLoc = Vector2D::Zero(), const std::string& inName = "Paddle") : Entity(inName)
    {
        Location = inLoc;
    }
    
    ~Paddle()
    {
        
    }

    void BeginPlay() override
    {
        Entity::BeginPlay();

        AddComponent<TransformComponent>();
        GetComponentByClass<TransformComponent>()->Location = Location;
        GetComponentByClass<TransformComponent>()->Scale = Vector2D(10, 100);
        AddComponent<RectComp>(0, 255, 0);
        AddComponent<CollisionComponent>();
        AddComponent<PaddleController>();
        
    }

    void Update(float deltaTime) override
    {
        Entity::Update(deltaTime);
    }

private:

    Vector2D Location{Vector2D::Zero()};
};