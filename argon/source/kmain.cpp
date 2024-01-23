#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "libcpp/StringView.hpp"

#include "system/descriptor/GDT.hpp"
#include "system/descriptor/IDT.hpp"
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
}

