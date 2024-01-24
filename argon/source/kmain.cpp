#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "Terminal.hpp"
#include "system/descriptor/GDT.hpp"
#include "system/descriptor/IDT.hpp"

extern "C" void kmain(void)
{
    Terminal::initialize();

    GDT::initialize();
    Terminal::putln("initialized GDT");

    IDT::initialize();
    Terminal::putln("initialized IDT");

    Terminal::putln("Hello, Kernel!", VGAColor::LIGHT_GREEN);
}

