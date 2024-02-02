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

auto execute_module(auto module, auto moduleName, auto&&... args)
{
    Array<char const*, 1 + sizeof...(args)> static programInfo { moduleName.data(), args... };
    auto* executable = reinterpret_cast<int(*)(int, char const**)>(module);

    return executable(programInfo.size(), programInfo.data());
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
    IDT::set_irq_handler(1, KeyBoard::keyboard_driver);

    auto const frequency = 60;
    auto const divisor   = 1193180 / frequency;

    port::outb(port::PIT_COMMAND, 0x36);

    port::outb(port::PIT_DATA, uint8_t(divisor));
    port::outb(port::PIT_DATA, uint8_t(divisor >> 8));

    asm ("sti");

    auto const* info = reinterpret_cast<multiboot_info_t const*>(ebx);

    Array<StringView, 3> static constexpr availableModules
    {
         "apply", "multiply", "validator"
    };

    if (CHECK_FLAG(info->flags, 3))
    {
        kassert(availableModules.size() == info->mods_count);
        Terminal::putf("available modules: {}\n", availableModules);
    }

    Terminal::put("\n");

    while (true)
    {
        Array<char, 255> command {};
        KeyBoard::read(command);

        auto const* modules = reinterpret_cast<multiboot_module_t*>(info->mods_addr);

        // cppcheck-suppress incorrectStringBooleanError
        if (starts_with(command.data(), availableModules[0])) kassert(false && "UNIMPLEMENTED");
        // cppcheck-suppress incorrectStringBooleanError
        else if (starts_with(command.data(), availableModules[1])) kassert(false && "UNIMPLEMENTED");
        else if (starts_with(command.data(), availableModules[2]))
        {
            auto constexpr moduleName = availableModules[2];

            auto result = 0;

            if (strlen(command.data()) > moduleName.size())
                result = execute_module(modules[2].mod_start, moduleName, command.data() + 1 + moduleName.size());
            else
                result = execute_module(modules[2].mod_start, moduleName);

            Terminal::putf("module `{}` exited with code {}\n", moduleName, result);
        }
        else
        {
            Terminal::putf("module `{}` doesn't exist.\n", command.data());
        }
    }

    for (;;) { asm ("hlt"); }
}

