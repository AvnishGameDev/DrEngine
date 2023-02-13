#pragma once

#include "../ECS.h"
#include "SDL_ttf.h"

namespace DrEngine::ECS
{
    class DRENGINE_API TextComp : public Component
    {
    public:
        TextComp(const std::string& font_path, int font_size, const std::string& message, const Color& color = Color(0, 0, 255))
        {
            fontPath = font_path;
            fontSize = font_size;
            text = message;
            textColor = color;

            RefreshTexture();
        }

        ~TextComp()
        {
            textTexture->Destroy();
        }

        void Draw(float deltaTime) override
        {
            if (bPulse)
            {
                int R, G, B;
                R = 0;
                G = static_cast<int>(SDL_fabsf(SDL_cosf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f));
                B = static_cast<int>(SDL_fabsf(SDL_sinf(static_cast<float>(SDL_GetTicks()) / 1000.0f) * 255.0f));
                
                SetColor(Color(R, G, B));
            }
            
            Application::GetRenderer()->RenderTexture(Location, Scale, textTexture);
        }

        void SetSize(int newSize)
        {
            fontSize = newSize;
            RefreshTexture();
        }
        
        void SetText(const std::string& newText)
        {
            text = newText;
            RefreshTexture();
        }
        
        void SetColor(const Color& color)
        {
            textColor = color;
            RefreshTexture();
        }
        
        void SetLocation(Vector2D inLoc) { Location = inLoc; }

        void SetPulse(bool inVal) { bPulse = inVal; };
        
    private:

        void RefreshTexture()
        {
            if (textTexture)
                textTexture->Destroy();
            textTexture = new Texture(fontPath, fontSize, text, textColor);
            int w, h;
            SDL_QueryTexture(textTexture->GetSDLTexture(), nullptr, nullptr, &w, &h);
            Scale = Vector2D(w, h);
        }
        
        bool bPulse{false};
        
        std::string fontPath;
        int fontSize;
        std::string text;
        Color textColor;
        
        Vector2D Location{Vector2D(20, 20)};
        Vector2D Scale{Vector2D::Zero()};
        Texture* textTexture{nullptr};
    };
}
