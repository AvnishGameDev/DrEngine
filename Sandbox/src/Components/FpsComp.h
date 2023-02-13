#pragma once

#include "DrEngine.h"

using namespace DrEngine::ECS;

class FpsComp : public Component
{
public:
    void BeginPlay() override
    {
        
    }

    void Update(float deltaTime) override
    {
        ++numFrames;
        Uint32 elapsedMS = SDL_GetTicks() - startTime; // Time since start of loop
        if (elapsedMS) { // Skip this the first frame
            double elapsedSeconds = elapsedMS / 1000.0; // Convert to seconds
            fps = static_cast<float>(numFrames / elapsedSeconds); // FPS is Frames / Seconds
        }
    }

    float GetFPS() const { return fps; };
private:
    float fps{0};
    int numFrames = 0;
    Uint32 startTime = SDL_GetTicks();
    
};