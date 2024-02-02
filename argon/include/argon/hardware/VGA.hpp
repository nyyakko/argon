#pragma once

#include <stddef.h>
#include <stdint.h>

#include <libcpp/Pair.hpp>

#include "VGAEntry.hpp"

class VGA
{
    VGA();

public:
    static constexpr size_t WIDTH  = 80;
    static constexpr size_t HEIGHT = 25;

    static VGA& initialize()
    {
        static VGA vga {};
        return vga;
    }

    static VGA& the() { return VGA::initialize(); }

    static void put_entry(VGAEntry const entry);
    static void clear_buffer(VGAColor const background = VGAColor::BLACK);
    static void set_cursor_position(size_t const x, size_t const y);
    static Pair<size_t, size_t> get_cursor_position();

private:
    uint16_t* buffer_m { reinterpret_cast<uint16_t*>(0xB8000) };
    size_t positionX_m {};
    size_t positionY_m {};
};

