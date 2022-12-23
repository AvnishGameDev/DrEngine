#pragma once

#include "Core.h"
#include "SDL.h"

class DRENGINE_API Window
{
public:
    Window();
    ~Window();

    bool Initialize(const char* title, int width, int height, bool fullscreen);
    void DestroyWindow();
    
private:
    SDL_Window* SDLwindow;
};
