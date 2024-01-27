#pragma once

#include <libcpp/StringView.hpp>

#include "hardware/VGA.hpp"
#include "hardware/VGAColor.hpp"

class Terminal
{
public:
    Terminal()
    {
        VGA::initialize();
    }

public:
    static Terminal& initialize()
    {
        static Terminal the {};
        return the;
    }

    static void put(char data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);
    static void put(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);
    static void putf(StringView format, ...);
    static void putln(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK);
};
