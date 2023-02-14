#pragma once

#include <string>

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "Application.h"
#include "Core.h"
#include "Log.h"
#include "Renderer.h"

namespace DrEngine
{
    namespace ECS
    {
        class Entity;
    }
    
    struct DRENGINE_API Color
    {
        Color()
        {
            R = 0;
            G = 0;
            B = 255;
            A = 255;
        }
        Color(float r, float g, float b, float a = 255)
        {
            R = r;
            G = g;
            B = b;
            A = a;
        }

        ~Color()
        {
            
        }

        SDL_Color ToSDLColor() const
        {
            SDL_Color color;
            color.r = static_cast<Uint8>(R);
            color.g = static_cast<Uint8>(G);
            color.b = static_cast<Uint8>(B);
            color.a = static_cast<Uint8>(A);
            return color;
        }
        
        void SetR(float inVal) { R = inVal; };
        void SetG(float inVal) { G = inVal; };
        void SetB(float inVal) { B = inVal; };
        void SetA(float inVal) { A = inVal; };
        
        float GetR() const { return R; };
        float GetG() const { return G; };
        float GetB() const { return B; };
        float GetA() const { return A; };

    private:
        float R, G, B, A;
    };

    struct DRENGINE_API Texture
    {
        Texture(std::string inPath)
        {
            imgPath = inPath;
            auto surface = IMG_Load(imgPath.c_str());
            if (!surface)
            {
                DE_ERROR("Failed to Create Surface from imgPath");
            }

            texture = SDL_CreateTextureFromSurface(Application::GetRenderer()->GetSDLRenderer(), surface);
            if (!texture)
            {
                DE_ERROR("Failed to Create Texture from Surface");
            }

            SDL_FreeSurface(surface);
        }

        Texture(const std::string& font_path, const int& font_size, const std::string& message, const Color& color)
        {
            TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
            if (!font)
            {
                DE_ERROR("Failed to load font.");
            }
            const auto textSurface = TTF_RenderText_Solid(font, message.c_str(), color.ToSDLColor());
            if (!textSurface)
            {
                DE_ERROR("Failed to create textSurface");
            }
            texture = SDL_CreateTextureFromSurface(Application::GetRenderer()->GetSDLRenderer(), textSurface);
            if (!texture)
            {
                DE_ERROR("Failed to create text Texture.");
            }

            SDL_FreeSurface(textSurface);
        }
        
        ~Texture()
        {
            SDL_DestroyTexture(texture);
        }

        void Destroy()
        {
            SDL_DestroyTexture(texture);
            delete this;
        }

        bool IsValid() const { return texture != nullptr; };
        
        std::string GetImgPath() const { return imgPath; };
        SDL_Texture* GetSDLTexture() const { return texture; };
        
    private:
        SDL_Texture* texture{nullptr};
        std::string imgPath;
    };

    struct CollisionData
    {
        CollisionData(ECS::Entity* inEntity, const bool& inHit = true)
        {
            OtherEntity = inEntity;
            bHit = inHit;
        }
        
        bool bHit = true;
        ECS::Entity* OtherEntity;
    };

    struct Audio
    {
        Audio(const std::string& inFilePath)
        {
            filePath = inFilePath;
            music = Mix_LoadMUS(filePath.c_str());
            if (!music)
            {
                DE_ERROR("Failed to load music: {0}", Mix_GetError());
            }
        }
        
        Mix_Music* GetSDLMusic() const { return music; };

        bool IsValid() const { return music != nullptr; };
        
    private:
        std::string filePath;
        Mix_Music* music;
    };
}
