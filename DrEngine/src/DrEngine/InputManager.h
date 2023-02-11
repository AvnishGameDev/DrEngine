#pragma once

#include "Core.h"

#include <SDL_keyboard.h>

namespace DrEngine
{
    enum MouseKey
    {
        Left,
        Right
    };
    
    class DRENGINE_API InputManager
    {
    public:

        InputManager()
        {
            
        }

        ~InputManager()
        {
            
        }

        void Update()
        {
            KeyboardState = SDL_GetKeyboardState(nullptr);
        }

        void PollEvent()
        {
            /* Set Mouse Coordinates */
            if (Application::event.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                Vector2D CurrentPos{Vector2D(x, y)};
                MouseDeltaPos = CurrentPos - MousePos;
                DE_INFO("({0},{1}) - ({2},{3}) = ({4},{5})", CurrentPos.X(), CurrentPos.Y(), MousePos.X(), MousePos.Y(), MouseDeltaPos.X(), MouseDeltaPos.Y());
                MousePos.SetX(x);
                MousePos.SetY(y);
            }
            else
            {
                MouseDeltaPos = Vector2D::Zero();
            }
            
            /* Set Mouse Button down */
            
            if (Application::event.type == SDL_MOUSEBUTTONDOWN)
            {
                if (Application::event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseLeftDown = true;
                }
                if (Application::event.button.button == SDL_BUTTON_RIGHT)
                {
                    mouseRightDown = true;
                }
            }
            else if (Application::event.type == SDL_MOUSEBUTTONUP)
            {
                if (Application::event.button.button == SDL_BUTTON_LEFT)
                {
                    mouseLeftDown = false;
                }
                if (Application::event.button.button == SDL_BUTTON_RIGHT)
                {
                    mouseRightDown = false;
                }
            }
        }

        void ResetMouseDelta() { MouseDeltaPos = Vector2D::Zero(); };
        
        /* Getters */
        
        bool KeyDown(SDL_Scancode KeyCode) const
        {
            return KeyboardState[KeyCode];
        }

        bool MouseKeyDown(MouseKey button)
        {
            switch (button)
            {
            case Left:
                return mouseLeftDown;
                break;
            case Right:
                return mouseRightDown;
                break;
            }
        }

        Vector2D GetMousePos() const { return MousePos; };
        Vector2D GetMouseDeltaPos() const { return MouseDeltaPos; };

    private:

        bool mouseLeftDown, mouseRightDown;

        Vector2D MouseDeltaPos;
        Vector2D MousePos;
        
        const Uint8* KeyboardState;
    };
}