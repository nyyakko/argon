#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "VGAColor.hpp"
#include "libcpp/conversion/BitCast.hpp"

class [[gnu::packed]] VGAEntry
{
public:
    constexpr VGAEntry(char const byte, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK):
        byte_m(byte), foreground_m(foreground), backgroun_m(background)
    {
    }

    explicit constexpr operator uint16_t(this auto self)
    {
        return bit_cast<uint16_t>(self);
    }

    auto constexpr byte(this auto self) { return self.byte_m; }
    auto constexpr foreground(this auto self) { return self.foreground_m; }
    auto constexpr background(this auto self) { return self.backgroun_m; }

private:
    [[maybe_unused]]char byte_m {};
    [[maybe_unused]]VGAColor foreground_m : 4 {};
    [[maybe_unused]]VGAColor backgroun_m : 4 {};
};

static_assert(sizeof(VGAEntry) == 2);

