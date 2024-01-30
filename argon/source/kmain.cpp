#include <libc/string.hpp>
#include <libcpp/Iota.hpp>

#include "Assert.hpp"
#include "Terminal.hpp"
#include "hardware/IO.hpp"
#include "hardware/MultiBoot.hpp"
#include "hardware/hid/KeyBoard.hpp"
#include "system/descriptor/GDT.hpp"
#include "system/descriptor/IDT.hpp"

void clock_driver(InterruptStack const*) {}

void run_apply(auto* program)
{
    auto value          = 69;
    auto const valueOld = 69;

    program([] (void* value) {
        *reinterpret_cast<int*>(value) *= 1000;
        *reinterpret_cast<int*>(value) += 420;
    }, &value);

    kassert(value == 69420);

    Terminal::putf("/external/executable/apply: given %d results %d\n", valueOld, value);
}

void run_multiply(auto* program)
{
    auto const lhs    = 69;
    auto const rhs    = 420;
    auto const result = program(lhs, rhs);

    kassert(result == lhs * rhs);

    Terminal::putf("/external/executable/multiply: given %d, %d results %d\n", lhs, rhs, result);
}

void run_verifier(auto* program)
{
    auto constexpr cpf = "12595771043";
    auto const result  = program(cpf);

    kassert(result == true);

    Terminal::putf("/external/executable/validator: %s is valid? %b\n", cpf, static_cast<bool>(result));
}

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
                run_apply(reinterpret_cast<void(*)(void(*)(void*), void const*)>(modules[index].mod_start));
                break;
            }
            case 1: {
                run_multiply(reinterpret_cast<int(*)(int, int)>(modules[index].mod_start));
                break;
            }
            case 2: {
                run_verifier(reinterpret_cast<bool(*)(char const*)>(modules[index].mod_start));
                break;
            }
            }
        }
    }

    Terminal::put("\n");

    asm ("sti");

    for (;;) { asm ("hlt"); }
}

