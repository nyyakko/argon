#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "descriptor/GDT.hpp"
#include "Terminal.hpp"

extern "C" void kmain(void)
{
    Terminal::initialize();
    Terminal::putln("Hello, Terminal!");

    GDT::initialize();
    Terminal::putln("Hello, GDT!");

    Terminal::putln("Hello, Kernel!");
}

