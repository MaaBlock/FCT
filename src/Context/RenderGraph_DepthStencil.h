//
// Created by Administrator on 2025/8/10.
//

#ifndef RENDERGRAPH_DEPTHSTENCIL_H
#define RENDERGRAPH_DEPTHSTENCIL_H
namespace FCT{
    struct DepthStencil
    {
        std::string name;
        Format format;
        Samples samples;
        uint32_t width;
        uint32_t height;
        bool hasFixedSize;

        Window* wnd;
        bool isWindow;

        DepthStencil() noexcept
            : name(""), format(Format::D32_SFLOAT), samples(Samples::sample_undefined),
              width(0), height(0), hasFixedSize(false), wnd(nullptr), isWindow(false) {}

        template<typename... Args>
        DepthStencil(std::string_view name, Args&&... args) noexcept
            : name(name), format(Format::D32_SFLOAT), samples(Samples::sample_undefined),
              width(0), height(0), hasFixedSize(false), wnd(nullptr), isWindow(false) {
            processArgs(std::forward<Args>(args)...);
        }

        template<typename... Rest>
        constexpr void processArgs(const Format& other, Rest&&... rest) noexcept {
            format = other;
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(const Samples& other, Rest&&... rest) noexcept {
            samples = other;
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(Window* window, Rest&&... rest) noexcept {
            wnd = window;
            isWindow = true;
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(uint32_t w, uint32_t h, Rest&&... rest) noexcept {
            width = w;
            height = h;
            hasFixedSize = true;
            processArgs(std::forward<Rest>(rest)...);
        }

        constexpr void processArgs() noexcept {}
    };
}
#endif //RENDERGRAPH_DEPTHSTENCIL_H
