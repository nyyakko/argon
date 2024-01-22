#pragma once

#include "libcpp/StringView.hpp"

#include "VGA.hpp"
#include "VGAColor.hpp"

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

    static void put(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK) noexcept
    {
        for (auto index = 0zu; index < data.size(); index++)
        {
            VGA::put_entry_at(VGAEntry(data.data()[index], foreground, background));
        }
    }

    static void putln(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK) noexcept
    {
        put(data, foreground, background);
        put("\n"_sv, foreground, background);
    }
};
