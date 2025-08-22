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

    namespace RHI
    {
        class Pass;
    }
    struct PassInfo
    {
        RHI::Pass& pass;
        std::map<std::string, Image*> textures;
        std::map<std::string, ShaderStage> textureSlot;
    };
    struct PipeHub {
        ObjectPipe<std::string> passPipe;

    };
}
#endif //PIPEHUB_H
