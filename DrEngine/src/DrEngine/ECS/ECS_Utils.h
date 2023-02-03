#pragma once

namespace DrEngine::ECS::Utils
{
    template <class DstType, class SrcType>
    static bool IsType(const SrcType* src)
    {
        return dynamic_cast<const DstType*>(src) != nullptr;
    }

    template <class DstType, class SrcType>
    static DstType* Cast(SrcType* src)
    {
        return dynamic_cast<DstType*>(src);
    }
}
