#pragma once

#include "Core.h"
#include "Application.h"

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

        void Init()
        {
            
        }
        
        void Update()
        {
            KeyboardState = SDL_GetKeyboardState(nullptr);
        }

        void PollEvent()
        {
            /* Set Mouse Coordinates */
            if (Application::GetEvent().type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                const Vector2D CurrentPos{Vector2D(static_cast<float>(x), static_cast<float>(y))};
                MouseDeltaPos = CurrentPos - MousePos;
                MousePos.SetX(static_cast<float>(x));
                MousePos.SetY(static_cast<float>(y));
            }
            else
            {
                MouseDeltaPos = Vector2D::Zero();
            }
            
            /* Set Mouse Button down */
            
            if (Application::GetEvent().type == SDL_MOUSEBUTTONDOWN)
            {
                if (Application::GetEvent().button.button == SDL_BUTTON_LEFT)
                {
                    mouseLeftDown = true;
                }
                if (Application::GetEvent().button.button == SDL_BUTTON_RIGHT)
                {
                    mouseRightDown = true;
                }
            }
            else if (Application::GetEvent().type == SDL_MOUSEBUTTONUP)
            {
                if (Application::GetEvent().button.button == SDL_BUTTON_LEFT)
                {
                    mouseLeftDown = false;
                }
                if (Application::GetEvent().button.button == SDL_BUTTON_RIGHT)
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
            return false;
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