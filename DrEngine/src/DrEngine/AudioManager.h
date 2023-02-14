#pragma once

#include "Core.h"
#include "SDL_mixer.h"
#include "Structs.h"

namespace DrEngine
{
    struct Audio;

    class DRENGINE_API AudioManager
    {
    public:

        void Init()
        {
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 1024) < 0)
            {
                DE_CORE_ERROR("Mix_OpenAudio Error: {0}", Mix_GetError());
            }
        }
        
        void PlayAudio(const Audio* inAudio, int noLoops = 0)
        {
            Mix_PlayMusic(inAudio->GetSDLMusic(), noLoops);
        }
    };
}
