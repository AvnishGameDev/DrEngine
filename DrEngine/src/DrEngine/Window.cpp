#include "Window.h"

#include "Renderer.h"
#include "SDL.h"

namespace DrEngine
{
    Window::Window()
    {
    }

    Window::~Window()
    {
        DestroyWindow();
    }

    bool Window::Initialize(const char* title, int width, int height, bool fullscreen)
    {
        SDLwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, fullscreen ? SDL_WINDOW_FULLSCREEN : 0 | SDL_WINDOW_SHOWN);
        if (SDLwindow == nullptr)
        {
            return false;
        }
        return true;
    }

    void Window::DestroyWindow()
    {
        SDL_DestroyWindow(SDLwindow);
    }

#pragma region GettersAndSetters
    
    void Window::SetRenderer(Renderer* inRenderer)
    {
        renderer = inRenderer;
    }

    Renderer* Window::GetRenderer() const
    {
        return renderer;
    }

    SDL_Window* Window::GetSDLWindow() const
    {
        return SDLwindow;
    }

#pragma endregion GettersAndSetters
}
