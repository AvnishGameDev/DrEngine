#pragma once

#include "SDL.h"

namespace DrEngine::Math
{
    static float SinF(float f)
    {
        return SDL_sinf(f);
    }

    static float CosF(float f)
    {
        return SDL_cosf(f);
    }

    static float TanF(float f)
    {
        return SDL_tanf(f);
    }
}
