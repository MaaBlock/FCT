//
// Created by Administrator on 2025/8/9.
//

#ifndef CLEARTYPES_H
#define CLEARTYPES_H
namespace FCT
{
    enum class ClearType : uint32_t
    {
        color = 0x1,
        depth = 0x2,
        stencil = 0x4,
        depthStencil = depth | stencil
    };
    FCT_DECLARE_FLAGS(ClearType);
}
#endif //CLEARTYPES_H
