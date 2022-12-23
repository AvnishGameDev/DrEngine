#include "Renderer.h"

#include "SDL.h"
#include "Window.h"

namespace DrEngine
{
    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
    }

    bool Renderer::Initialize(Window* window)
    {
        SDLrenderer = SDL_CreateRenderer(window->GetSDLWindow(), -1, SDL_RENDERER_ACCELERATED);
        if (SDLrenderer == nullptr)
        {
            return false;
        }
        return true;
    }
}
