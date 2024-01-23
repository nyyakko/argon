#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "libcpp/conversion/BitCast.hpp"

#include "VGAColor.hpp"

class [[gnu::packed]] VGAEntry
{
public:
    explicit constexpr VGAEntry(char const byte, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK):
        byte_m(byte), foreground_m(foreground), backgroun_m(background)
    {
    }

    // cppcheck-suppress functionConst
    explicit constexpr operator uint16_t(this auto self)
    {
        return bit_cast<uint16_t>(self);
    }

    // cppcheck-suppress functionStatic
    auto constexpr byte(this auto self) { return self.byte_m; }
    // cppcheck-suppress functionStatic
    auto constexpr foreground(this auto self) { return self.foreground_m; }
    // cppcheck-suppress functionStatic
    auto constexpr background(this auto self) { return self.backgroun_m; }

private:
    [[maybe_unused]]char byte_m {};
    [[maybe_unused]]VGAColor foreground_m : 4 {};
    [[maybe_unused]]VGAColor backgroun_m : 4 {};
};

static_assert(sizeof(VGAEntry) == 2);

