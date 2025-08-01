

#ifndef FLAGS_H
#define FLAGS_H
#include "../ThirdParty.h"
#include <type_traits>

namespace FCT
{
    template <typename BitType>
    struct FlagTraits;

    //learning from vulkan-hpp
    /**
     * @cond CHINESE
     * @tips 使用方法：
     * @code
     *    enum XX {
     *      flag1 = 1 << 0,
     *      flag1 = 1 << 1
     *    };
     *    FCT_DECLARE_FLAGS(XX);
     * @endcode
     * 这样就定义了一个 XXs flag
     * @tparam BitType
     * @endcond
     */
    template <typename BitType>
    class Flags {
    public:
        using MaskType = typename std::underlying_type<BitType>::type;

        constexpr Flags() noexcept : m_mask(0) {}
        constexpr Flags(BitType bit) noexcept : m_mask(static_cast<MaskType>(bit)) {}
        constexpr Flags(Flags<BitType> const & rhs) noexcept = default;
        constexpr explicit Flags(MaskType flags) noexcept : m_mask(flags) {}

        constexpr bool operator<(Flags<BitType> const & rhs) const noexcept { return m_mask < rhs.m_mask; }
        constexpr bool operator<=(Flags<BitType> const & rhs) const noexcept { return m_mask <= rhs.m_mask; }
        constexpr bool operator>(Flags<BitType> const & rhs) const noexcept { return m_mask > rhs.m_mask; }
        constexpr bool operator>=(Flags<BitType> const & rhs) const noexcept { return m_mask >= rhs.m_mask; }
        constexpr bool operator==(Flags<BitType> const & rhs) const noexcept { return m_mask == rhs.m_mask; }
        constexpr bool operator!=(Flags<BitType> const & rhs) const noexcept { return m_mask != rhs.m_mask; }

        constexpr bool operator!() const noexcept { return !m_mask; }

        constexpr Flags<BitType> operator&(Flags<BitType> const & rhs) const noexcept { return Flags<BitType>(m_mask & rhs.m_mask); }
        constexpr Flags<BitType> operator|(Flags<BitType> const & rhs) const noexcept { return Flags<BitType>(m_mask | rhs.m_mask); }
        constexpr Flags<BitType> operator^(Flags<BitType> const & rhs) const noexcept { return Flags<BitType>(m_mask ^ rhs.m_mask); }
        constexpr Flags<BitType> operator~() const noexcept { return Flags<BitType>(~m_mask); }

        Flags<BitType> & operator=(Flags<BitType> const & rhs) noexcept = default;
        Flags<BitType> & operator=(BitType bit) noexcept { m_mask = static_cast<MaskType>(bit); return *this; }
        Flags<BitType> & operator|=(Flags<BitType> const & rhs) noexcept { m_mask |= rhs.m_mask; return *this; }
        Flags<BitType> & operator&=(Flags<BitType> const & rhs) noexcept { m_mask &= rhs.m_mask; return *this; }
        Flags<BitType> & operator^=(Flags<BitType> const & rhs) noexcept { m_mask ^= rhs.m_mask; return *this; }

        explicit constexpr operator bool() const noexcept { return !!m_mask; }
        explicit constexpr operator MaskType() const noexcept { return m_mask; }



    private:
        MaskType m_mask;
    };

    template <typename BitType>
    struct FlagTraits
    {
        static constexpr bool isBitmask = false;
    };

    template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
    constexpr Flags<BitType> operator|(BitType lhs, BitType rhs) noexcept
    {
        return Flags<BitType>(lhs) | Flags<BitType>(rhs);
    }

    template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
    constexpr Flags<BitType> operator&(BitType lhs, BitType rhs) noexcept
    {
        return Flags<BitType>(lhs) & Flags<BitType>(rhs);
    }

    template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
    constexpr Flags<BitType> operator^(BitType lhs, BitType rhs) noexcept
    {
        return Flags<BitType>(lhs) ^ Flags<BitType>(rhs);
    }

    template <typename BitType, typename std::enable_if<FlagTraits<BitType>::isBitmask, bool>::type = true>
    constexpr Flags<BitType> operator~(BitType bits) noexcept
    {
        return ~(Flags<BitType>(bits));
    }

    template <typename BitType>
    constexpr Flags<BitType> operator|(BitType bit, Flags<BitType> const& flags) noexcept
    {
        return flags | bit;
    }

    template <typename BitType>
    constexpr Flags<BitType> operator&(BitType bit, Flags<BitType> const& flags) noexcept
    {
        return flags & bit;
    }

    template <typename BitType>
    constexpr Flags<BitType> operator^(BitType bit, Flags<BitType> const& flags) noexcept
    {
        return flags ^ bit;
    }


    #define FCT_DECLARE_FLAGS(BitType) \
        template<> \
        struct FCT::FlagTraits<BitType> \
        { \
            static constexpr bool isBitmask = true; \
        }; \
        using BitType##s = FCT::Flags<BitType>;

    #define FCT_DECLARE_FLAG(BitType,flags) \
        template<> \
        struct FCT::FlagTraits<BitType> \
        { \
        static constexpr bool isBitmask = true; \
        }; \
        using flags = FCT::Flags<BitType>;
    #define FCT_TO_FLAG(name,translateBitFunc,FlagBitType,FlagType) \
        inline auto name(FlagType flags) \
        { \
            auto result = translateBitFunc(static_cast<FlagBitType>(0)) | translateBitFunc(static_cast<FlagBitType>(0)); \
                for (uint32_t i = 0; i < 32; ++i) { \
                    FlagBitType singleFlag = static_cast<FlagBitType>(1u << i); \
                    if (flags & singleFlag) { \
                        result |= translateBitFunc(singleFlag); \
                    } \
                } \
            return result; \
        }
    #define FCT_TO_FLAGS(name,translateBitFunc,FlagBitType) FCT_TO_FLAG(name, translateBitFunc, FlagBitType, FlagBitType##s)
#ifdef FCT_USE_VULKAN
    #define FCT_TO_VK_FLAG_BIT_BEGIN(FlagBit) \
        inline vk::##FlagBit##FlagBits ToVk##FlagBit(FlagBit bit) \
        { \
            switch (bit) \
            {
    #define FCT_TO_VK_FLAG_BIT_CASE(FlagBit,value,Value) \
            case FlagBit::value: \
                return vk::##FlagBit##FlagBits::e##Value;
    #define FCT_TO_VK_FLAG_BIT_END(FlagBit) \
            default: \
                return vk::##FlagBit##FlagBits(0); \
            } \
        }
    #define FCT_TO_VK_FLAGS(FlagBit) \
        FCT_TO_FLAGS(ToVk##FlagBit##s,ToVk##FlagBit,FlagBit)
#endif
}

#endif //FLAGS_H