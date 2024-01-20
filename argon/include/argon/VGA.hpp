#pragma once

#include <stddef.h>
#include <stdint.h>

#include "IO.hpp"
#include "VGAColor.hpp"
#include "VGAEntry.hpp"
#include "libcpp/StringView.hpp"

auto set_cursor_position(auto const x, auto const y)
{
    auto const position = 80 * y + x;

    io::outb(io::ports::FB_COMMAND_PORT, 14);
    io::outb(io::ports::FB_DATA_PORT, (position >> 8) & 0x00FF);
    io::outb(io::ports::FB_COMMAND_PORT, 15);
    io::outb(io::ports::FB_DATA_PORT, position & 0x00FF);
}

class VGA
{
    static constexpr size_t VGA_WIDTH  = 80;
    static constexpr size_t VGA_HEIGHT = 25;

    VGA()
    {
        for (size_t y = 0; y < VGA_HEIGHT; y++)
        {
            for (size_t x = 0; x < VGA_WIDTH; x++)
                buffer_s[y * VGA_WIDTH + x] = static_cast<uint16_t>(VGAEntry(' '));
        }

        VGA::putln("VGA: i am alive!\n", VGAColor::LIGHT_GREEN);

        set_cursor_position(0, 1);
    }

public:
    static VGA& initialize()
    {
        static VGA the {};
        return the;
    }

    static void put(char const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK)
    {
        VGAEntry const entry { data, foreground, background };
        auto const position = y_s * VGA_WIDTH + x_s;

        if (entry.byte() == '\n' || entry.byte() == '\b')
        {
            if (entry.byte() == '\n')
            {
                y_s = (y_s < VGA_HEIGHT) ? y_s += 1 : 0;
                x_s = 0;
            }
            else if (entry.byte() == '\b')
            {
                buffer_s[position - 1] = static_cast<uint16_t>(VGAEntry(' '));
                x_s -= 1;
            }

            set_cursor_position(x_s, y_s);

            return;
        }

        set_cursor_position(x_s + 1, y_s);

        buffer_s[position] = static_cast<uint16_t>(entry);
        x_s = (x_s < VGA_WIDTH) ? x_s += 1 : 0;
    }

    static void put(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK)
    {
        for (auto index = 0zu; index < data.size(); index++)
        {
            put(data.data()[index], foreground, background);
        }
    }

    static void putln(StringView const data, VGAColor const foreground = VGAColor::LIGHT_GREY, VGAColor const background = VGAColor::BLACK)
    {
        put(data, foreground, background);
        put("\n"_sv, foreground, background);
    }

private:
    static uint16_t* buffer_s;
    static size_t x_s;
    static size_t y_s;
};

inline auto VGA::buffer_s = reinterpret_cast<uint16_t*>(0xB8000);
inline auto VGA::x_s      = 0zu;
inline auto VGA::y_s      = 0zu;

