//
// Created by Administrator on 2025/8/10.
//

#ifndef RENDERGRAPHENABLEPASSCLEAR_H
#define RENDERGRAPHENABLEPASSCLEAR_H
namespace FCT {
    struct EnablePassClear
    {
        ClearTypes types;
        Vec4 color;
        float depth;
        uint8_t stencil;
        EnablePassClear() noexcept : types(0), color(0.0f, 0.0f, 0.0f, 1.0f), depth(1.0f), stencil(0) {}
        template<typename... Args>
        constexpr EnablePassClear(Args&&... args) noexcept : types(0), color(0.0f, 0.0f, 0.0f, 1.0f), depth(1.0f), stencil(0)
        {
            processArgs(std::forward<Args>(args)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const ClearTypes& other, Rest&&... rest)
        {
            types = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(Vec4&& other, Rest&&... rest)
        {
            color = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const float& other, Rest&&... rest)
        {
            depth = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        constexpr void processArgs(const uint8_t& other, Rest&&... rest)
        {
            stencil = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        constexpr void processArgs() noexcept {}
    };
}
#endif //RENDERGRAPHENABLEPASSCLEAR_H
