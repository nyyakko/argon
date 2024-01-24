#pragma once

#include <stddef.h>
#include <stdint.h>

#include "VGAEntry.hpp"

inline void set_cursor_position(size_t const x, size_t const y);

class VGA
{
    static constexpr size_t WIDTH  = 80;
    static constexpr size_t HEIGHT = 25;

    VGA();

public:
    static VGA& initialize()
    {
        static VGA the {};
        return the;
    }

    static void put_entry_at(VGAEntry const entry);
    static void clear_buffer(VGAColor const background = VGAColor::BLACK);

    static size_t x_s;
    static size_t y_s;

private:
    static uint16_t* buffer_s;
};

inline auto VGA::buffer_s = reinterpret_cast<uint16_t*>(0xB8000);
inline auto VGA::x_s      = 0zu;
inline auto VGA::y_s      = 0zu;

void set_cursor_position(size_t const x, size_t const y);
