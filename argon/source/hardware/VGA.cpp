#include "hardware/VGA.hpp"

#include "hardware/io/IO.hpp"

VGA::VGA()
{
    this->clear_buffer();
}

void VGA::clear_buffer(VGAColor background)
{
    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
            buffer_s[y * WIDTH + x] = static_cast<uint16_t>(VGAEntry(' ', VGAColor::LIGHT_GREY, background));
    }

    set_cursor_position(0, 0);
}

void VGA::put_entry_at(VGAEntry const entry)
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


void set_cursor_position(size_t const x, size_t const y)
{
    auto const position = 80 * y + x;

    outb(port::FB_COMMAND, 14);
    outb(port::FB_DATA, (position >> 8) & 0x00FF);
    outb(port::FB_COMMAND, 15);
    outb(port::FB_DATA, position & 0x00FF);

    VGA::x_s = x;
    VGA::y_s = y;
}

