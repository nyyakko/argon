#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <libcpp/conversion/BitCast.hpp>

#include "VGAColor.hpp"

class [[gnu::packed]] VGAEntry
{
public:
    explicit constexpr VGAEntry(char const byte, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK):
        byte_m(byte), foreground_m(foreground), backgroun_m(background)
    {
    }

    explicit constexpr operator uint16_t() const
    {
        return bit_cast<uint16_t>(*this);
    }

    auto constexpr byte() const { return this->byte_m; }
    auto constexpr foreground() const { return this->foreground_m; }
    auto constexpr background() const { return this->backgroun_m; }

private:
    [[maybe_unused]]char byte_m {};
    [[maybe_unused]]VGAColor foreground_m : 4 {};
    [[maybe_unused]]VGAColor backgroun_m : 4 {};
};

static_assert(sizeof(VGAEntry) == 2);

