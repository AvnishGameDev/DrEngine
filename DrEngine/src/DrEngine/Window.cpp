#include "Window.h"

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
}

void Window::DestroyWindow()
{
    SDL_DestroyWindow(SDLwindow);
}
