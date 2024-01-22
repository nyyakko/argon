#pragma once

#include <stddef.h>
#include <stdint.h>

#include "PortIO.hpp"
#include "VGAEntry.hpp"

inline void set_cursor_position(size_t const x, size_t const y);

class VGA
{
    static constexpr size_t WIDTH  = 80;
    static constexpr size_t HEIGHT = 25;

    VGA() noexcept
    {
        for (size_t y = 0; y < HEIGHT; y++)
        {
            for (size_t x = 0; x < WIDTH; x++)
                buffer_s[y * WIDTH + x] = static_cast<uint16_t>(VGAEntry(' '));
        }
    }

public:
    static VGA& initialize() noexcept
    {
        static VGA the {};
        return the;
    }

    static void put_entry_at(VGAEntry const entry) noexcept
    {
        auto const position = y_s * WIDTH + x_s;

        if (entry.byte() == '\n' || entry.byte() == '\b')
        {
            if (entry.byte() == '\n')
            {
                set_cursor_position(0, (y_s < HEIGHT) ? y_s += 1 : 0);
            }
            else if (entry.byte() == '\b')
            {
                buffer_s[position - 1] = static_cast<uint16_t>(VGAEntry(' '));
                set_cursor_position(x_s - 1, y_s);
            }

            return;
        }

        buffer_s[position] = static_cast<uint16_t>(entry);
        set_cursor_position((x_s < WIDTH) ? x_s += 1 : 0, y_s);
    }

    static size_t x_s;
    static size_t y_s;

private:
    static uint16_t* buffer_s;
};

inline auto VGA::buffer_s = reinterpret_cast<uint16_t*>(0xB8000);
inline auto VGA::x_s      = 0zu;
inline auto VGA::y_s      = 0zu;

inline void set_cursor_position(size_t const x, size_t const y)
{
    auto const position = 80 * y + x;

    io::outb(io::ports::FB_COMMAND_PORT, 14);
    io::outb(io::ports::FB_DATA_PORT, (position >> 8) & 0x00FF);
    io::outb(io::ports::FB_COMMAND_PORT, 15);
    io::outb(io::ports::FB_DATA_PORT, position & 0x00FF);

    VGA::x_s = x;
    VGA::y_s = y;
}

