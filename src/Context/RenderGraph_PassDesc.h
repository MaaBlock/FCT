//
// Created by Administrator on 2025/8/10.
//

#ifndef RENDERGRAPH_PASSDESC_H
#define RENDERGRAPH_PASSDESC_H
namespace FCT
{

    struct PassDesc
    {
        std::string name;
        EnablePassClear clear = EnablePassClear();
        std::vector<Texture> textures;
        std::vector<Target> targets;
        std::vector<DepthStencil> depthStencils;
        PassDesc(std::string name) : name(name)
        {
        }
        template<typename... Rest>
        void processArgs(const EnablePassClear& other, Rest&&... rest)
        {
            clear = other;
            processArgs(std::forward<Rest>(rest)...);
        }
        template<typename... Rest>
        void processArgs(const Texture& other, Rest&&... rest)
        {
            textures.push_back(other);
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        void processArgs(const Target& other, Rest&&... rest)
        {
            targets.push_back(other);
            processArgs(std::forward<Rest>(rest)...);
        }

        template<typename... Rest>
        void processArgs(const DepthStencil& other, Rest&&... rest)
        {
            depthStencils.push_back(other);
            processArgs(std::forward<Rest>(rest)...);
        }


        void processArgs() noexcept {}
    };
}
#endif //RENDERGRAPH_PASSDESC_H
