#pragma once

#include "libcpp/StringView.hpp"

#include "hardware/VGA.hpp"
#include "hardware/VGAColor.hpp"

class Terminal
{
public:
    Terminal() noexcept
    {
        VGA::initialize();
    }

public:
    static Terminal& initialize() noexcept
    {
        static Terminal the {};
        return the;
    }

    static void put(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK) noexcept;
    static void putln(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK) noexcept;
};
