#ifndef RENDERGRAPH_TEXTURESIZE_H
#define RENDERGRAPH_TEXTURESIZE_H
namespace FCT {
    struct TextureSize
    {
        enum class Type {
            Absolute,
            Relative,
            Undefined // 等同于FullSize
        };

        Type type;
        uint32_t width;
        uint32_t height;
        //TextureSize = Target * RelativeScale
        Fraction relativeWidth;
        Fraction relativeHeight;

        TextureSize(uint32_t w, uint32_t h) noexcept
            : type(Type::Absolute), width(w), height(h), relativeWidth(1), relativeHeight(1) {}

        TextureSize(const Fraction& relW, const Fraction& relH) noexcept
            : type(Type::Relative), width(0), height(0), relativeWidth(relW), relativeHeight(relH) {}

        TextureSize(int32_t numW, int32_t denW, int32_t numH, int32_t denH) noexcept
            : type(Type::Relative), width(0), height(0), 
              relativeWidth(numW, denW), relativeHeight(numH, denH) {}

        TextureSize() noexcept
            : type(Type::Undefined), width(0), height(0), relativeWidth(1), relativeHeight(1) {}

        static TextureSize Absolute(uint32_t w, uint32_t h) { 
            return TextureSize(w, h); 
        }
        
        static TextureSize Relative(const Fraction& w, const Fraction& h) { 
            return TextureSize(w, h); 
        }
        
        static TextureSize Relative(int32_t numW, int32_t denW, int32_t numH, int32_t denH) { 
            return TextureSize(numW, denW, numH, denH); 
        }
        
        static TextureSize FullSize() { 
            return TextureSize(Fraction(1), Fraction(1)); 
        }
        
        static TextureSize HalfSize() { 
            return TextureSize(Fraction(1, 2), Fraction(1, 2)); 
        }
        
        static TextureSize QuarterSize() { 
            return TextureSize(Fraction(1, 4), Fraction(1, 4)); 
        }

        // 添加一些常用的分数大小
        static TextureSize ThirdSize() { 
            return TextureSize(Fraction(1, 3), Fraction(1, 3)); 
        }
        
        static TextureSize TwoThirdsSize() { 
            return TextureSize(Fraction(2, 3), Fraction(2, 3)); 
        }
        
        static TextureSize ThreeQuartersSize() { 
            return TextureSize(Fraction(3, 4), Fraction(3, 4)); 
        }

        // 检查是否为单位大小（1:1）
        bool isFullSize() const noexcept {
            return type == Type::Relative && 
                   relativeWidth.isUnit() && relativeHeight.isUnit();
        }

        // 获取相对大小的浮点值（用于兼容性）
        float getRelativeWidthFloat() const noexcept {
            return relativeWidth.toFloat();
        }

        float getRelativeHeightFloat() const noexcept {
            return relativeHeight.toFloat();
        }
    };
}
#endif //RENDERGRAPH_TEXTURESIZE_H