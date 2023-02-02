#include "Manager.h"
#include "Entity.h"
#include "../Log.h"

namespace DrEngine::ECS
{

    Entity* Manager::AddEntity()
    {
        auto* e = new Entity();
        EntityBitset[currentEntitySlot++] = true;
        Entities.push_back(e);
        return e;
    }

    void Manager::DestroyEntity(Entity*& e)
    {
        for (auto itr = Entities.begin(); itr < Entities.end(); ++itr)
        {
            if (*itr == e)
            {
                EntityBitset[std::distance(Entities.begin(), itr)] = false;
                Entities.erase(itr);
                delete e;
                e = nullptr;
            }
        }
    }
}
