//
// Created by Administrator on 2025/8/10.
//

#ifndef RENDERGRAPH_TEXTURE_H
#define RENDERGRAPH_TEXTURE_H
namespace FCT
{
    struct Texture
    {
        std::string name;
        Format format;
        Samples samples;
        ShaderStages stages;
        TextureSize size;

        Texture() noexcept : size(TextureSize::FullSize()) {}

        template<typename... Args>
        Texture(std::string_view name, Args&&... args) noexcept
            : name(name), format(Format::UNDEFINED), samples(Samples::sample_undefined),
              stages(ShaderStage::Fragment), size(TextureSize()) {
            processArgs(std::forward<Args>(args)...);
        }

        template<typename... Rest>
        constexpr void processArgs(const Samples& other, Rest&&... rest) noexcept {
            samples = other;
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(const Format& other, Rest&&... rest) noexcept {
            format = other;
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(const ShaderStages& other, Rest&&... rest) noexcept {
            stages = other;
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(const TextureSize& other, Rest&&... rest) noexcept {
            size = other;
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        constexpr void processArgs(uint32_t width, uint32_t height, Rest&&... rest) noexcept {
            size = TextureSize::Absolute(width, height);
            processArgs(std::forward<Rest>(rest)...);
        }

        constexpr void processArgs() noexcept {}
    };
}
#endif //RENDERGRAPH_TEXTURE_H
