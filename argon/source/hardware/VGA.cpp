#include "hardware/VGA.hpp"

#include <libcpp/Iota.hpp>
#include <libc/string.hpp>

#include "hardware/IO.hpp"

VGA::VGA()
{
    this->clear_buffer();
}

void VGA::clear_buffer(VGAColor const background)
{
    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
            buffer_s[y * WIDTH + x] = static_cast<uint16_t>(VGAEntry(' ', VGAColor::LIGHT_GREY, background));
    }

    VGA::set_cursor_position(0, 0);
}

void VGA::put_entry(VGAEntry const entry)
{
    auto const position = y_s * WIDTH + x_s;

    switch (entry.byte())
    {
    case '\n':
        if (y_s < HEIGHT - 1)
            y_s += 1;
        else
        {
            memmove(buffer_s, &buffer_s[WIDTH], (HEIGHT - 1) * WIDTH);
            memset(&buffer_s[(HEIGHT - 1) * WIDTH], static_cast<uint16_t>(VGAEntry(' ')), WIDTH);
        }

        VGA::set_cursor_position(0, y_s);
        return;
    case '\t':
        for ([[maybe_unused]]auto _ : Iota(0, 4))
            VGA::put_entry(VGAEntry(' '));
        return;
    case '\b':
        // FIXME: maybe should return to previous line ?
        VGA::set_cursor_position(x_s ? x_s -= 1 : 0, y_s);
        buffer_s[y_s * WIDTH + x_s] = static_cast<uint16_t>(VGAEntry(' '));
        return;
    }

    buffer_s[position] = static_cast<uint16_t>(entry);

    if (x_s < WIDTH)
        x_s += 1;
    else
    {
        x_s  = 0;
        y_s += 1;
    }

    VGA::set_cursor_position(x_s, y_s);
}

void VGA::set_cursor_position(size_t const x, size_t const y)
{
    auto const position = 80 * y + x;

    outb(port::FB_COMMAND, 14);
    outb(port::FB_DATA, (position >> 8) & 0x00FF);
    outb(port::FB_COMMAND, 15);
    outb(port::FB_DATA, position & 0x00FF);

    VGA::x_s = x;
    VGA::y_s = y;
}

Pair<size_t, size_t> VGA::get_cursor_position()
{
    return { VGA::x_s, VGA::y_s };
}

