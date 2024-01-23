#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "libcpp/StringView.hpp"

#include "GDT.hpp"
#include "IDT.hpp"
#include "Terminal.hpp"

extern "C" void kmain(void)
{
    Terminal::initialize();
    Terminal::putln("Hello, Terminal!");
    GDT::initialize();
    Terminal::putln("Hello, GDT!");
    IDT::initialize();
    Terminal::putln("Hello, IDT!");

    Terminal::putln("Hello, Kernel!");

    // look at this! it crashes the kernel!

    auto result = 0;

    for (auto a = 5, b = 5; b >= 0; b -= 1)
    {
        result = a/b;
    }

    (void)result;
}

