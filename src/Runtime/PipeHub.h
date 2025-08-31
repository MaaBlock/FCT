//
// Created by Administrator on 2025/8/21.
//

#ifndef PIPEHUB_H
#define PIPEHUB_H
#include "../Base/ObjectPipe.h"
#include "../Context/ShaderStage.h"

namespace FCT
{
    class Image;
    class Window;

    namespace RHI
    {
        class Pass;
    }

    struct OutputInfo
    {
        bool isWindow;
        Window* window;
        uint32_t width;
        uint32_t height;
        
        OutputInfo() : isWindow(false), window(nullptr), width(0), height(0) {}
        OutputInfo(bool isWnd, Window* wnd = nullptr, uint32_t w = 0, uint32_t h = 0)
            : isWindow(isWnd), window(wnd), width(w), height(h) {}
    };

    struct PassInfo
    {
        RHI::Pass& pass;
        std::map<std::string, Image*> textures;
        std::map<std::string, ShaderStage> textureSlot;
        std::map<std::string, Image*> targets;
        std::map<std::string, Image*> depthStencils;
        OutputInfo outputInfo;
    };
    struct PipeHub {
        ObjectPipe<std::string> passPipe;

    };
}
#endif //PIPEHUB_H
