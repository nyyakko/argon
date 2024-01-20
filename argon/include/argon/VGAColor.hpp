#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum class VGAColor : uint8_t
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE,
};

static_assert(static_cast<uint8_t>(VGAColor::WHITE) == 15);

