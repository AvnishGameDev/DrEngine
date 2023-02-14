#pragma once

#include "Vector2D.h"
#include "TrigFunctions.h"

namespace DrEngine::Math
{
    static float AbsF(float inVal)
    {
        return SDL_fabsf(inVal);
    }
}
