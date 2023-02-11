#include "Collision.h"
#include "ECS/ECS.h"

#include <SDL.h>

using namespace DrEngine::ECS;

namespace DrEngine
{
    bool Collision::AABB(const CollisionComponent* colA, const CollisionComponent* colB)
    {
        SDL_Rect* rectA = new SDL_Rect();
        rectA->x = colA->GetTransform()->GetLocation().X();
        rectA->y = colA->GetTransform()->GetLocation().Y();
        rectA->w = colA->GetTransform()->GetScale().X();
        rectA->h = colA->GetTransform()->GetScale().Y();

        SDL_Rect* rectB = new SDL_Rect();
        rectB->x = colB->GetTransform()->GetLocation().X();
        rectB->y = colB->GetTransform()->GetLocation().Y();
        rectB->w = colB->GetTransform()->GetScale().X();
        rectB->h = colB->GetTransform()->GetScale().Y();
        
        const bool bResult =
        rectA->x + rectA->w >= rectB->x &&
        rectB->x + rectB->w >= rectA->x &&
        rectA->y + rectA->h >= rectB->y &&
        rectB->y + rectB->h >= rectA->y;
        
        delete rectA;
        delete rectB;
        return bResult;
    }
}