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

        bool operator == (const Vector2D& vec2) const
        {
            return this->X() == vec2.X() && this->Y() == vec2.Y();
        }
        
        Vector2D operator + (const Vector2D& vec2) const
        {
            Vector2D finalVec;
            finalVec.SetX(this->X() + vec2.X());
            finalVec.SetY(this->Y() + vec2.Y());
            return finalVec;
        }
        
    private:
        float x{0};
        float y{0};
    };
}
