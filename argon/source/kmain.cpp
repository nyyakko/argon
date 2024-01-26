#include "Terminal.hpp"
#include "descriptor/GDT.hpp"
#include "descriptor/IDT.hpp"
#include "hardware/IO.hpp"
#include "hardware/hid/KeyBoard.hpp"

void clock_driver(Registers const*) {}

extern "C" void kmain(void)
{
    Terminal::initialize();

    GDT::initialize();
    Terminal::putln("initialized GDT");
    IDT::initialize();
    Terminal::putln("initialized IDT");

    Terminal::putln("Hello, Argon!");

    IDT::set_irq_handler(0, clock_driver);
    IDT::set_irq_handler(1, keyboard_driver);

    auto const frequency = 50;
    auto const divisor   = 1193180 / frequency;

    outb(0x43, 0x36);

    outb(0x40, uint8_t(divisor));
    outb(0x40, uint8_t(divisor >> 8));

    asm ("sti");

    for (;;) { asm ("hlt"); }
}

