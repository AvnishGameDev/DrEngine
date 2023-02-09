#pragma once

#include "../Core.h"

namespace DrEngine
{
    class DRENGINE_API Vector2D
    {
    public:
        Vector2D()
        {
            x = 0;
            y = 0;
        }
        
        Vector2D(float inX, float inY)
        {
            x = inX;
            y = inY;
        }

        float X() const { return x; }
        float Y() const { return y; }
        void SetX(float inVal) { x = inVal; }
        void SetY(float inVal) { y = inVal; }

        static Vector2D Zero() { return Vector2D(); };
        
    private:
        float x{0};
        float y{0};
    };
}
