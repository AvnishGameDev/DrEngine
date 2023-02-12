#pragma once

#include "../ECS.h"
#include "SDL_ttf.h"

namespace DrEngine::ECS
{
    class DRENGINE_API TextComp : public Component
    {
    public:
        TextComp(const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color = {0, 0, 255, 255})
        {
            fontPath = font_path;
            fontSize = font_size;
            text = message;
            textColor = color;
            
            textTexture = loadFont(font_path, font_size, message, color);
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
        }

        ~TextComp()
        {
            SDL_DestroyTexture(textTexture);
        }

        void Draw() override
        {
            if (bPulse)
            {
                int R, G, B;
                R = 0;
                G = SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);
                B = SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f);

                SDL_Color col;
                col.r = R;
                col.g = G;
                col.b = B;
                col.a = 255;
                SetColor(col);
            }
            
            textRect.x = Location.X();
            textRect.y = Location.Y();
            SDL_RenderCopy(Application::renderer->GetSDLRenderer(), textTexture, nullptr, &textRect);
        }

        static SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color)
        {
            TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
            if (!font)
            {
                DE_ERROR("Failed to load font.");
                return nullptr;
            }
            auto textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
            if (!textSurface)
            {
                DE_ERROR("Failed to create textSurface");
                return nullptr;
            }
            SDL_Texture* texture = SDL_CreateTextureFromSurface(Application::renderer->GetSDLRenderer(), textSurface);
            if (!texture)
            {
                DE_ERROR("Failed to create text Texture.");
                return nullptr;
            }

            SDL_FreeSurface(textSurface);
            return texture;
        }

        void SetSize(int newSize)
        {
            fontSize = newSize;
            SDL_DestroyTexture(textTexture);
            textTexture = loadFont(fontPath, fontSize, text, textColor);
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
        }
        
        void SetText(const std::string& newText)
        {
            text = newText;
            SDL_DestroyTexture(textTexture);
            textTexture = loadFont(fontPath, fontSize, text, textColor);
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
        }
        
        void SetColor(const SDL_Color& color)
        {
            textColor = color;
            SDL_DestroyTexture(textTexture);
            textTexture = loadFont(fontPath, fontSize, text, color);
            SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
        }
        
        void SetLocation(Vector2D inLoc) { Location = inLoc; }

        void SetPulse(bool inVal) { bPulse = inVal; };
        
    private:

        bool bPulse{false};
        
        std::string fontPath;
        int fontSize;
        std::string text;
        SDL_Color textColor;
        
        Vector2D Location{Vector2D(20, 20)};
        SDL_Texture* textTexture{nullptr};
        SDL_Rect textRect;
    };
}