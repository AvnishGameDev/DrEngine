#pragma once

#include "Core.h"

namespace DrEngine
{
    class Renderer;
}

#include "SDL.h"

namespace DrEngine
{
    class DRENGINE_API Window
    {
    public:
        Window();
        ~Window();

        bool Initialize(const char* title, int width, int height, bool fullscreen);
        void DestroyWindow();
        
        /* Getters and Setters */
    
        void SetRenderer(Renderer* inRenderer);
        Renderer* GetRenderer() const;

        SDL_Window* GetSDLWindow() const;
    
    private:
        SDL_Window* SDLwindow;
        Renderer* renderer;
    };
}
