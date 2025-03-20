#pragma once

#include "XTypeDef.h"
#include <cassert>

namespace ID
{
    using IDType = u32;

    constexpr IDType InvalidID{IDType(-1)};
    constexpr u32 MinDeletedElements{1024};

    namespace detail
    {
        constexpr u32 gen_bits{10};                             // 用于表示生成次数的位数
        constexpr u32 idx_bits{sizeof(IDType) * 8 - gen_bits};  // 剩余为数用于索引
        constexpr IDType idx_mask{(IDType(1) << idx_bits) - 1}; // 索引掩码
        constexpr IDType gen_mask{(IDType(1) << gen_bits) - 1}; // 生成掩码
    }

    using GenIDType = std::conditional_t<detail::gen_bits <= 16,
                                         std::conditional_t<detail::gen_bits <= 8, u8, u16>, u32>;

    static_assert(sizeof(GenIDType) * 8 >= detail::gen_bits);
    static_assert((sizeof(IDType) - sizeof(GenIDType)) > 0);

    // 检查ID是否有效
    constexpr bool IsValidID(IDType id)
    {

        return id != InvalidID;
    }

    // 提取索引部分
    constexpr IDType IDIndex(IDType id)
    {
        IDType index{id & detail::idx_mask};
        assert(index != detail::idx_mask);
        return index;
    }

    // 生成 ID
    constexpr IDType GenID(IDType id)
    {
        return (id >> detail::idx_bits) & detail::gen_mask;
    }

    // 生成新 ID
    constexpr IDType NewGenID(IDType id)
    {
        const IDType gen{GenID(id) + 1};
        assert(gen < (((u64)1 << detail::gen_bits) - 1));
        return IDIndex(id) | (gen << detail::idx_bits);
    }

#if _DEBUG
    namespace detail
    {
        struct IDBase
        {
            constexpr explicit IDBase(IDType id) : _id{id} {}
            constexpr operator IDType() const { return _id; }

        private:
            IDType _id;
        };
    } // detail namespace

#define DEFINE_TYPED_ID(name)              \
    struct name final : ID::detail::IDBase \
    {                                      \
        constexpr explicit name(ID::IDType id) \
            : IDBase{id} {}                \
        constexpr name() : IDBase{0} {}    \
    };
#else
#define DEFINE_TYPED_ID(name) using name = ID::IDType;
#endif
}