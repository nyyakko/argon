#include "Assert.hpp"
#include "Terminal.hpp"
#include "hardware/IO.hpp"
#include "hardware/MultiBoot.hpp"
#include "hardware/hid/KeyBoard.hpp"
#include "system/descriptor/GDT.hpp"
#include "system/descriptor/IDT.hpp"

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

    auto const* info = reinterpret_cast<multiboot_info_t const*>(ebx);

    if (CHECK_FLAG(info->flags, 3))
    {
        Terminal::putf("loaded modules: %d\n\n", info->mods_count);

        auto const* modules = reinterpret_cast<multiboot_module_t*>(info->mods_addr);

        for (auto index = 0zu; index != info->mods_count; index += 1)
        {
            switch (index)
            {
            case 0: {
                auto value          = 69;
                auto const valueOld = 69;

                using signature_t = void(*)(void(*)(void*), void const*);
                reinterpret_cast<signature_t>(modules[index].mod_start)([] (void* value) {
                    *reinterpret_cast<int*>(value) *= 1000;
                    *reinterpret_cast<int*>(value) += 420;
                }, &value);

                kassert(value == 69421);
                Terminal::putf("/external/executable/apply: given %d results %d\n", valueOld, value);

                break;
            }
            case 1: {
                auto const lhs = 69;
                auto const rhs = 420;

                using signature_t = int(*)(int, int);
                auto const result = reinterpret_cast<signature_t>(modules[index].mod_start)(lhs, rhs);

                kassert(result == lhs * rhs);
                Terminal::putf("/external/executable/multiply: given %d, %d results %d\n", lhs, rhs, result);
                break;
            }
            }
        }
    }

    Terminal::put("\n");

    asm ("sti");

    for (;;) { asm ("hlt"); }
}

