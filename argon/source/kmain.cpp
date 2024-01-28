#include <libcpp/Iota.hpp>

#include "Terminal.hpp"
#include "hardware/IO.hpp"
#include "hardware/hid/KeyBoard.hpp"
#include "system/descriptor/GDT.hpp"
#include "system/descriptor/IDT.hpp"

void clock_driver(InterruptStack const*)
{
    auto static tick = 0;

    if (tick % (2 * 60) == 0)
    {
        auto static counter = 0;
        auto [x, y] = VGA::get_cursor_position();
        VGA::set_cursor_position(0, 0);
        Terminal::putf("tick: %d", counter += 1);
        VGA::set_cursor_position(x, y);
    }

    tick += 1;
}

extern "C" void kmain(void)
{
    Terminal::initialize();
    GDT::initialize();
    Terminal::putln("\n\ninitialized GDT", VGAColor::LIGHT_GREEN);
    IDT::initialize();
    Terminal::putln("initialized IDT\n", VGAColor::LIGHT_GREEN);

    Terminal::putln("Hello, Argon!\n");

    IDT::set_irq_handler(0, clock_driver);
    IDT::set_irq_handler(1, keyboard_driver);

    auto const frequency = 60;
    auto const divisor   = 1193180 / frequency;

    outb(port::PIT_COMMAND, 0x36);

    outb(port::PIT_DATA, uint8_t(divisor));
    outb(port::PIT_DATA, uint8_t(divisor >> 8));

    asm ("sti");

    for (;;) { asm ("hlt"); }
}

