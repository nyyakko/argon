#include "hardware/VGA.hpp"

#include <libcpp/Iota.hpp>
#include <libc/string.hpp>

#include "hardware/IO.hpp"

VGA::VGA()
{
    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
            buffer_m[y * WIDTH + x] = static_cast<uint16_t>(VGAEntry(' ', VGAColor::LIGHT_GREY, VGAColor::BLACK));
    }

    port::outb(port::FB_COMMAND, 14);
    port::outb(port::FB_DATA, 0);
    port::outb(port::FB_COMMAND, 15);
    port::outb(port::FB_DATA, 0);
}

void VGA::clear_buffer(VGAColor const background)
{
    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
            VGA::the().buffer_m[y * WIDTH + x] = static_cast<uint16_t>(VGAEntry(' ', VGAColor::LIGHT_GREY, background));
    }

    VGA::set_cursor_position(0, 0);
}

void VGA::put_entry(VGAEntry const entry)
{
    auto const position = VGA::the().positionY_m * WIDTH + VGA::the().positionX_m;

    switch (entry.byte())
    {
    case '\n':
        if (VGA::the().positionY_m < HEIGHT - 1)
            VGA::the().positionY_m += 1;
        else
        {
            memmove(VGA::the().buffer_m, &VGA::the().buffer_m[WIDTH], (HEIGHT - 1) * WIDTH);
            memset(&VGA::the().buffer_m[(HEIGHT - 1) * WIDTH], static_cast<uint16_t>(VGAEntry(' ')), WIDTH);
        }

        VGA::set_cursor_position(0, VGA::the().positionY_m);
        return;
    case '\t':
        for ([[maybe_unused]]auto _ : Iota(0, 4))
            VGA::put_entry(VGAEntry(' '));
        return;
    case '\b':
        // FIXME: maybe should return to previous line ?
        VGA::set_cursor_position(VGA::the().positionX_m ? VGA::the().positionX_m -= 1 : 0, VGA::the().positionY_m);
        VGA::the().buffer_m[VGA::the().positionY_m * WIDTH + VGA::the().positionX_m] = static_cast<uint16_t>(VGAEntry(' '));
        return;
    }

    VGA::the().buffer_m[position] = static_cast<uint16_t>(entry);

    if (VGA::the().positionX_m < WIDTH)
        VGA::the().positionX_m += 1;
    else
    {
        VGA::the().positionX_m  = 0;
        VGA::the().positionY_m += 1;
    }

    VGA::set_cursor_position(VGA::the().positionX_m, VGA::the().positionY_m);
}

void VGA::set_cursor_position(size_t const x, size_t const y)
{
    auto const position = 80 * y + x;

    port::outb(port::FB_COMMAND, 14);
    port::outb(port::FB_DATA, (position >> 8) & 0x00FF);
    port::outb(port::FB_COMMAND, 15);
    port::outb(port::FB_DATA, position & 0x00FF);

    VGA::the().positionX_m = x;
    VGA::the().positionY_m = y;
}

Pair<size_t, size_t> VGA::get_cursor_position()
{
    return { VGA::the().positionX_m, VGA::the().positionY_m };
}

