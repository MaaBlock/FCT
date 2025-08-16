//
// Created by Administrator on 2025/5/4.
//
#include "./Freetype_FontCommon.h"

#include "Freetype_Font.h"
#include "../DebugTools/OutStream.h"

namespace FCT
{
    void Freetype_FontCommon::init()
    {
        if (FT_Init_FreeType(&g_library))
            fout << "Could not initialize FreeType library" << std::endl;
    }
    Freetype_Font *Freetype_FontCommon::create()
    {
        return new Freetype_Font(this);
    }

    void Freetype_FontCommon::tern()
    {
        FT_Done_FreeType(g_library);
    }
}
