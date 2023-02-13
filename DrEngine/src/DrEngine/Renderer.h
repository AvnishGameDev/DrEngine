#pragma once

#include "Core.h"

namespace DrEngine
{
    class Window;
}
struct SDL_Renderer;

namespace DrEngine
{
    class DRENGINE_API Renderer
    {
    public:
        Renderer();
        ~Renderer();

        bool Initialize(Window* window);
    
        SDL_Renderer* GetSDLRenderer() const { return SDLrenderer; };
    
    private:
        SDL_Renderer* SDLrenderer;
    };
}
