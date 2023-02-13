#include "Renderer.h"

#include "SDL.h"
#include "Window.h"
#include "Structs.h"

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

    void Renderer::RenderRect(const Vector2D& Location, const Vector2D& Scale, const Color& color)
    {
        SDL_Rect* rect = new SDL_Rect();
        rect->x = Location.X();
        rect->y = Location.Y();
        rect->w = Scale.X();
        rect->h = Scale.Y();
        
        SDL_SetRenderDrawColor(SDLrenderer, color.GetR(), color.GetG(), color.GetB(), color.GetA());
        SDL_RenderFillRect(SDLrenderer, rect);

        delete rect;
    }

    void Renderer::RenderTexture(const Vector2D& Location, const Vector2D& Scale, const Texture* texture)
    {
        SDL_Rect* rect = new SDL_Rect();
        rect->x = static_cast<int>(Location.X());
        rect->y = static_cast<int>(Location.Y());
        rect->w = static_cast<int>(Scale.X());
        rect->h = static_cast<int>(Scale.Y());
            
        if (texture && texture->IsValid())
        {
            SDL_RenderCopy(SDLrenderer, texture->GetSDLTexture(), nullptr, rect);
        }
        else
        {
            DE_ERROR("texture not valid!");
        }

        delete rect;
    }

    void Renderer::RenderPoint(const Vector2D& Location)
    {
        SDL_RenderDrawPoint(SDLrenderer, Location.X(), Location.Y());
    }
}
