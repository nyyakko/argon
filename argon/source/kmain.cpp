#include "Terminal.hpp"
#include "hardware/IO.hpp"
#include "hardware/hid/KeyBoard.hpp"
#include "system/descriptor/GDT.hpp"
#include "system/descriptor/IDT.hpp"
#include "hardware/MultiBoot.hpp"

void clock_driver(InterruptStack const*) {}

extern "C" void kmain([[maybe_unused]]unsigned int ebx)
{
    Terminal::initialize();

    GDT::initialize();
    Terminal::putln("initialized GDT", VGAColor::LIGHT_GREEN);
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

#if 0
    auto const* info = reinterpret_cast<multiboot_info_t const*>(ebx);

    if (CHECK_FLAG(info->flags, 3))
    {
        Terminal::putf("programs loaded: %d\n", info->mods_count);

        if (info->mods_count == 1)
        {
            auto* module  = reinterpret_cast<multiboot_module_t*>(info->mods_addr);
            auto* program = reinterpret_cast<int(*)(int, int)>(module->mod_start);
            Terminal::putf("%d * %d result: %d", 2, 8, program(2, 8));
        }
    }
#endif

    asm ("sti");

    for (;;) { asm ("hlt"); }
}

