//
// Created by Administrator on 2025/8/9.
//

#ifndef SHADERSTAGE_H
#define SHADERSTAGE_H
#include "../Base/Flags.h"
namespace FCT {

    enum class ShaderStage : uint32_t {
        Vertex          = 0x00000001,
        Fragment        = 0x00000002,
        Compute         = 0x00000004,
        Geometry        = 0x00000008,
        TessControl     = 0x00000010,
        TessEvaluation  = 0x00000020,
        Mesh            = 0x00000040,
        Task            = 0x00000080,
        RayGen          = 0x00000100,
        AnyHit          = 0x00000200,
        ClosestHit      = 0x00000400,
        Miss            = 0x00000800,
        Intersection    = 0x00001000,
        Callable        = 0x00002000,
        All             = 0xFFFFFFFF
    };
    FCT_DECLARE_FLAGS(ShaderStage);


    inline ShaderStage getEarliestStage(ShaderStages stages) {
        if (stages & ShaderStage::Vertex) {
            return ShaderStage::Vertex;
        }
        if (stages & ShaderStage::Geometry) {
            return ShaderStage::Geometry;
        }
        if (stages & ShaderStage::Fragment) {
            return ShaderStage::Fragment;
        }
        if (stages & ShaderStage::Compute) {
            return ShaderStage::Compute;
        }

        return static_cast<ShaderStage>(0);
    }

}
#endif //SHADERSTAGE_H
